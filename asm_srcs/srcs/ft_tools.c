#include "asm.h"

extern t_op op_tab[17];

int   ft_nb_split(char *str, int i)
{
  int   nb;

  nb = 0;
  ft_printf("nb:%c\n", str[i + nb]);
  while (ft_split_param(str[i + nb]))
  {
  ft_printf("nb:%c\n", str[i + nb]);
    nb++;
  }
  return (nb);
}

int   ft_split_param(char c)
{
  if (ft_isspace(c) || c == SEPARATOR_CHAR)
    return (1);
  return (0);
}

int   ft_find_op(char *op)
{
  int   i;

  i = 0;
  while (i < 17 && ft_strcmp(op_tab[i].param, op) != 0)
    i++;
  if (op_tab[i].param == 0)
    return (-1);
  return (i);
}

char *ft_erspace(char *str)
{
  int   i;
  int   j;
  char  *tmp;

  j = 0;
  tmp = NULL;
  i = ft_strlen(str) - 1;
  while (i > 0 && ft_isspace(str[i]))
  {
    if (ft_isspace(str[i]))
      str[i] = '\0';
    i--;
  }
  while (str[j] && str[j] == ' ')
    j++;
  tmp = str + j;
  return (tmp);
}
