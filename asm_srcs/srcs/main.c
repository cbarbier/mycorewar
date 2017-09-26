/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:16:47 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/26 17:41:33 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_isopt(char c)
{
	if (c == 'o')
		return (1);
	if (c == 'a')
		return (2);
	if (c == '-')
		return (3);
	return (0);
}

static int		ft_check_main_args(char *str)
{
	int i;
	int	flag;
	int dash;
	int	res;

	i = 0;
	res = 0;
	dash = 0;
	if (str[0] != '-' || !ft_strcmp(str, "--"))
		return (0);
	while (str[i])
	{
		flag = 0;
		if (str[i] == '-')
			dash++;
		if (dash > 1 || !(flag = ft_isopt(str[i])))
		{
			ft_printf("asm: illegal option -- %c\n", str[i]);
			return (-1);
		}
		else
		{
			if (flag == 1)
			{
				if (res == 0 || res == 2)
					res += 1;
			}
			else if (flag == 2)
			{
				if (res < 2)
					res += 2;
			}
		}
		i++;
	}
	return (res);
}

int		main(int ac, char **av)
{
	int		i;
	int		oa;
	int		res;
	char	*str;
	char	*rnm;

	oa = 0;
	i = 1;
	str = NULL;
	rnm = NULL;
	if (ac < 2)
	{
		ft_printf("Usage: ./asm [-a][-o output file] <sourcefile.s>\n\
	-a: print an annoted version of the code instead of creating a .cor file\n\
	-o: use the output file as name instead of the default name\n");
		return (0);
	}
	while (av[i])
	{
		res = ft_check_main_args(av[i]);
		if (res == -1)
		{
			ft_printf("Usage: ./asm [-a][-o output file] <sourcefile.s>\n\
		-a: print an annoted version of the code instead of creating a .cor file\n\
		-o: use the output file as name instead of the default name\n");
		return (0);
		}
		else if (res == 1 || res == 3)
		{
			if (av[i + 1])
			{
				if (av[i + 1][0] == '-')
				{
					ft_printf("Usage: ./asm [-a][-o output file] <sourcefile.s>\n\
				-a: print an annoted version of the code instead of creating a .cor file\n\
				-o: use the output file as name instead of the default name\n");
					return (0);
				}
				rnm = av[i + 1];	
			}
			i++;
		}
		else if (res == 0)
		{
			if (ft_strcmp("--", av[i]))
				str = av[i]; 
			else
			{
				if (av[i + 1])
					str = av[i + 1];
			}
			break ;
		}
		i++;
		if (oa < res)
			oa = res;
	}
	ft_launcher(str, rnm, oa);
	return (0);
}
