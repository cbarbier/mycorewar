/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_head.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 11:44:23 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/11 15:47:22 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_erase_dc(char *str)
{
	char	*tmp;

	tmp = str + 1;
	tmp[ft_strlen(tmp) - 1] = '\0';
	return (tmp);
}

static int ft_error_header(t_asm *sfile, int flag)
{
	if (flag != -2)
	{
		if (!sfile->name)
			ft_printf("Name missing\n");
		else if (!sfile->comment)
			ft_printf("Comment missing\n");
	}
	return (0);
}

int		ft_parse_head(t_asm *sfile, char *line, int flag)
{
	char	**tab;
	if (line && line[0] != '\0' && line[0] != '\n' && line[0] != COMMENT_CHAR)
	{
		tab = ft_strsplitnbif(line, ft_isspace, 1);
		if (flag == 0 && tab && tab[0] && ft_strcmp(tab[0],
					NAME_CMD_STRING) == 0)
		{
			flag++;
			if (tab && tab[1] && tab[1][0] && tab[1][ft_strlen(tab[1]) - 1]
					== '"')
				sfile->name = ft_strdup(ft_erase_dc(tab[1]));
			else
			{
				ft_printf("Name wrong format\n");
				return (-2);
			}
		}
		else if (flag == 1 && tab && tab[0] && ft_strcmp(tab[0],
					COMMENT_CMD_STRING) == 0)
		{
			flag++;
			if (tab && tab[1] && tab[1][0] && tab[1][ft_strlen(tab[1]) - 1]
					== '"')
				sfile->comment = ft_strdup(ft_erase_dc(line + 9));
			else
			{
				ft_printf("Comment wrong format\n");
				return (-2);
			}
		}
		else
			return (-1);
		ft_free_strtab(tab);
	}
	return (flag);
}

int		ft_head(t_asm *sfile)
{
	int		i;
	int		ret;
	int		flag;
	char	*line;
	char	*tmp;

	i = 0;
	flag = 0;
	while ((ret = get_next_line(sfile->fd, &line) > 0) && flag < 2)
	{
		tmp = ft_erspace(line);
		if ((flag = ft_parse_head(sfile, tmp, flag)) < 0)
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
		i++;
	}
	if (ret < 0 || !sfile->name || !sfile->comment)
		return (ft_error_header(sfile, flag));
		if (ft_strlen(sfile->name) > PROG_NAME_LENGTH)
		{
			ft_printf("Name too long\n");
			return (0);
		}
		else if (ft_strlen(sfile->comment) > COMMENT_LENGTH)
		{
			ft_printf("Comment too long\n");
			return (0);
		}
	ft_set_header(sfile);
	return (1);
}
