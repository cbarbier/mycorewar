#include "asm.h"

static int   ft_size(t_champ *node)
{
  int size;

  size = 0;
  if (node->instr == 1)
  {
    if (node->op && (ft_strcmp(node->op, "zjmp") == 0 ||
          ft_strcmp(node->op, "live") == 0 || ft_strcmp(node->op, "fork") == 0 ||
          ft_strcmp(node->op, "lfork") == 0))
      size += node->size + 1;
    else
      size += node->size + 2;
  }
  node = node->next;
  return(size);
}

static int   ft_total_size(t_champ *champ)
{
  int   total;

  total = 0;
  while (champ)
  {
    if (champ->instr == 1)
      total += ft_size(champ);
    champ = champ->next;
  }
  return (total);
}

void  ft_write(t_asm *sfile, t_champ *champ)
{
  int     size;
  int     binlen;
  int     fd;
  unsigned char    *bin;
  unsigned char    *tmp;

  binlen = PROG_NAME_LENGTH + COMMENT_LENGTH;
  bin = ft_memalloc(binlen + ft_total_size(champ));
  ft_memcpy(bin, sfile->header, binlen);
  tmp = bin + binlen;
  while (champ)
  {
    if (champ->instr == 1)
    {
      size = ft_size(champ);
//      ft_printf("instr:%s\n",champ->op);
//      ft_printf("size:%d\n", size);
      ft_memcpy(tmp, champ->param, size);
      tmp += size;
      binlen += size;
    }
    champ = champ->next;
  }
  fd = open(sfile->file, O_CREAT | O_WRONLY | S_IRWXU);
  write(fd, bin, binlen);
  ft_printf("   Compilation succeeded.\n");
  close(fd);
}
