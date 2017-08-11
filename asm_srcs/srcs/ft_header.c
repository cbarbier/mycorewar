#include "asm.h"

int		ft_magik_nbr(char *str)
{
  int i;
  int exe;

  i = 3;
  exe = COREWAR_EXEC_MAGIC;
  while (i >= 0)
  {
    str[i] = exe; 
    exe >>= 8;
    i--;
  }
	return (3);
}

int		ft_dump_name(t_asm *sfile, int i)
{
	int		j;

	j = 0;
	while (sfile->name[j])
	{
		sfile->header[i + j] = sfile->name[j];
		j++;
	}
	return (PROG_NAME_LENGTH);
}

int		ft_dump_comment(t_asm *sfile, int i)
{
	int		j;

	j = 0;
	while (sfile->comment[j])
	{
		sfile->header[i + j] = sfile->comment[j];
		j++;
	}
	return (PROG_NAME_LENGTH + COMMENT_LENGTH);
}

int		ft_set_header(t_asm *sfile)
{
	int		i;

	i = 0;
	while (i < PROG_NAME_LENGTH + COMMENT_LENGTH)
	{
		if (i == 0)
			i = ft_magik_nbr(sfile->header);
		else if (i < PROG_NAME_LENGTH)
			i = ft_dump_name(sfile, i);
		else if (i < COMMENT_LENGTH)
			i = ft_dump_comment(sfile, i + 11);
		i++;
	}
	return (1);
}


