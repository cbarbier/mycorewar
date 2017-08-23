#include "asm.h"

extern t_op op_tab[17];

int   ft_isspe(char *op)
{
  if (op && (ft_strcmp(op, "zjmp")  == 0 ||
        ft_strcmp(op, "live") == 0 || ft_strcmp(op, "fork") == 0 ||
        ft_strcmp(op, "lfork") == 0))
    return (1);
  return (0);

}
int   ft_prelabel(t_champ *node, char *label)
{
  int size;

  size = 0;
  while (node)
  {
    if (node->instr == 1)
    {
      if (ft_isspe(node->op))
        size += node->size + 1;
      else
        size += node->size + 2;
    }
    if (node->lab == 1 && ft_strcmp(node->label, label) == 0)
      return (size);
    node = node->next;
  }
  return(-1);
}

int   ft_postlabel(t_champ *champ, t_champ *node)
{
  int size;

  size = 0;
  while (node)
  {
    if (champ == node)
      return (-size);
    if (node->instr == 1)
    {
      if (ft_isspe(node->op))
        size += node->size + 1;
      else
        size += node->size + 2;
    }
    node = node->next;
  }
  return (-1);
}

int   ft_label(char *label, t_champ *champ, t_champ *save)
{
  char  *lab;

  lab = ft_strjoin(label, ":", 0);
  while (save)
  {
    if (save == champ)
      return (ft_prelabel(save, lab));
    if (save->lab == 1 && ft_strcmp(lab, save->label) == 0)
      return (ft_postlabel(champ, save));
    save = save->next;
  }
  return (-1);
}

void  ft_col(t_champ *champ)
{
  int   i;

  i = 0;
  while (champ->line[i] != LABEL_CHAR)
    i++;
  champ->col = i - 1;
}

int   ft_set_instr(t_champ *champ, t_champ *save)
{
  int i;
  int size;
  int res;

  i = 0;
  if (!ft_isspe(champ->op) || ft_strcmp("live",champ->op) == 0)
    size = 1;
  else
    size = 0;
  res = 0;
  while (champ->arg[i])
  {
    champ->codage <<= 2;
    if (champ->arg[i][0] == 'r')
    {
      size += REG_SIZE;
      champ->param[size] = ft_atoi(champ->arg[i] + 1);
      champ->codage |= REG_CODE; 
    }
    else if (champ->arg[i][0] == DIRECT_CHAR)
    {
      if (champ->arg[i][1] == LABEL_CHAR)
      {
        size += IND_SIZE;
        if ((res = ft_label(champ->arg[i] + 2, champ, save)) == -1)
        {
          champ->err = 1;
          champ->errcode = 7;
          ft_col(champ);
          return (0);
        }
        champ->param[size - 1] = res >> 8; 
        champ->param[size] = res;
      }
      else
      {
        if (ft_strcmp(champ->op, "live") == 0)
          size += 3;
        else if (ft_strcmp(champ->op, "zjmp") == 0 ||
            ft_strcmp(champ->op, "sti") == 0 || ft_strcmp(champ->op,
              "fork") == 0 || ft_strcmp(champ->op, "lfork") == 0)
          size += IND_SIZE;
        else
          size += DIR_SIZE;
        champ->param[size] = ft_atoi(champ->arg[i] + 1);
      }
      champ->codage |= DIR_CODE; 
    }
    else
    {
      size += IND_SIZE;
      champ->codage |= IND_CODE; 
      champ->param[size] = ft_atoi(champ->arg[i]);
    }
    i++;
  }
  while (i < 4)
  {
    champ->codage <<= 2;
    i++;
  }
  return (1);
}

int   ft_instr(t_champ *champ)
{
//  int i;
  int err;
  t_champ *save;

  err = 0;
  save = champ;
  while (champ)
  {
 //   i = 0;
    if (champ->instr == 1)
    {
      champ->param = ft_memalloc(champ->size + 2);
      champ->param[0] = champ->opcode;
      if (!ft_set_instr(champ, save))
        err = 1;
      if (!ft_isspe(champ->op))
        champ->param[1] = champ->codage;
/*      ft_printf("op:%s\nopcode:%d\ncodage:%x\narg:\n",champ->op, champ->opcode, champ->codage);
      while (champ->arg[i])
      {
        ft_printf("    %s\n",champ->arg[i]);
        i++;
      }
      i = 0;
      ft_printf("param:\n");
      while (i < champ->size + 2)
      {
        ft_printf("%.2x ",champ->param[i]);
        i++;
      }
      ft_printf("\nsize:%d\n",champ->size);
  */
    }
  champ = champ->next;
  }
  if (err == 1)
    return (0);
  return (1);
}
