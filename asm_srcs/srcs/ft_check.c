#include "asm.h"

extern t_op op_tab[17];

int   ft_check_args(char *arg, int itab, int i, t_champ *champ)
{
  if (arg[0] == 'r' && (op_tab[itab].arg[i] == 3 || op_tab[itab].arg[i]
    == 5 || op_tab[itab].arg[i] == 7 || op_tab[itab].arg[i] == 1))
    champ->size += REG_SIZE;
  else if (arg[0] == DIRECT_CHAR && (op_tab[itab].arg[i] == 3 ||
    op_tab[itab].arg[i] == 6 || op_tab[itab].arg[i] == 7 ||
    op_tab[itab].arg[i] == 2))
  {
    if  (ft_strcmp(champ->op, "zjmp") == 0 || 
      ft_strcmp(champ->op, "sti") == 0 || 
      ft_strcmp(champ->op, "fork") == 0 || 
      ft_strcmp(champ->op, "lfork") == 0)
      champ->size += IND_SIZE;
    else
      champ->size += DIR_SIZE;
  }
  else if (ft_isstrdigit(arg) && (op_tab[itab].arg[i] == 5 ||
    op_tab[itab].arg[i] == 6 || op_tab[itab].arg[i] == 7 ||
    op_tab[itab].arg[i] == 4))
    champ->size += IND_SIZE;
  else
  {
    champ->err = 1;
    champ->errcode = 5;
    return (0);
  }
  ft_printf("arg:%s champ->col:%d strlen:%d split:%d\n", arg, champ->col,  ft_strlen(arg), ft_nb_split(champ->args, champ->col - (ft_strlen(champ->op) + 1))); 
  champ->col += ft_strlen(arg) + ft_nb_split(champ->args, champ->col - (ft_strlen(champ->op) + 1)); 
  return (1);
}

int   ft_check_param(char *param, int itab, t_champ *champ)
{
  char **arg;
  int   nbtab;
  int   i;

  nbtab = 0;
  i = 0;
  arg = ft_strsplitif(param, ft_split_param);
  while (arg[nbtab])
    nbtab++;
  if (nbtab < op_tab[itab].nbargs || (nbtab > op_tab[itab].nbargs
        && arg[op_tab[itab].nbargs][0] != COMMENT_CHAR))
    return (0);
  while (arg[i] && i < op_tab[itab].nbargs)
  {
    if (!ft_check_args(arg[i], itab, i, champ))
      return (0);
    champ->arg = ft_strtab(champ->arg, arg[i]);
    i++;
  }
  return (1);
}

int   ft_check(char *op, char *param, t_champ *champ)
{
  int   i;

  i = 0;
  if (op == NULL)
    return (0);
  if (param == NULL)
  {
    if (ft_strchr(op, LABEL_CHAR) != 0)
    {
      champ->lab = 1;
      champ->label = ft_strdup(ft_erspace(op));
      return (1);
    }
    else
    {
      champ->err = 1;
      if ((i = ft_find_op(op)) == -1)
        champ->errcode = 3;
      else
        champ->errcode = 4;
      return (0);
    }
  }
  champ->instr = 1;
  if ((i = ft_find_op(op)) == -1)
  {
    champ->err = 1;
    champ->errcode = 3;
    return (0);
  }
  else
  {
    champ->op = ft_strdup(ft_erspace(op));
    champ->opcode = i + 1;
    champ->args = ft_strdup(param);
    champ->col = ft_strlen(champ->op) + 1;
  }
  if (!ft_check_param(param, i, champ))
    return (0);
  return (1);
}
