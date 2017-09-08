/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 11:40:56 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/08 11:42:19 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_champ		*ft_lst(t_asm *sfile, t_champ *champ)
{
	if (champ == NULL)
	{
		champ = ft_memalloc(sizeof(t_champ));
		sfile->champ = champ;
	}
	else
	{
		champ->next = ft_memalloc(sizeof(t_champ));
		champ = champ->next;
	}
	return (champ);
}

int			ft_parse(t_asm *sfile, t_champ *champ)
{
	int		i;
	int		ret;
	int		err;
	char	*line;
	char	*tmp;
	char	**op_param;

	i = 0;
	err = 0;
	while ((ret = get_next_line(sfile->fd, &line)) > 0)
	{
		tmp = ft_erspace(line);
		if (tmp && tmp[0] != '\0' && tmp[0] != '\n' && tmp[0] != COMMENT_CHAR)
		{
			champ = ft_lst(sfile, champ);
			champ->line = ft_strdup(tmp);
			champ->ligne = i;
			op_param = ft_strsplitnbif(tmp, ft_isspace, 1);
			if (!ft_check(op_param[0], op_param[1], champ))
				err = 1;
		}
		free(line);
		i++;
	}
	if (ret == -1 || err == 1)
		return (0);
	return (1);
}

int			ft_asm(t_asm *sfile, t_champ *champ)
{
	if (!ft_parse(sfile, champ))
	{
		champ = sfile->champ;
		ft_error(sfile);
		return (0);
	}
	champ = sfile->champ;
	if (!ft_instr(champ))
	{
		ft_error(sfile);
		return (0);
	}
	return (1);
}
