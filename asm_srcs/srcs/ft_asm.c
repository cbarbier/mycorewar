/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 11:40:56 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/11 18:59:07 by fmaury           ###   ########.fr       */
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

int			ft_precheck(char **op_param, t_champ *champ, t_asm *sfile)
{
	char	**rop_param;

	if (op_param[1])
		rop_param = ft_strsplitnbif(op_param[1], ft_isspace, 1);
	if (op_param[0] && op_param[0][ft_strlen(op_param[0]) - 1]  == LABEL_CHAR 
			&& rop_param[0] && ft_find_op(rop_param[0]) != -1)
	{
		champ->lab = 1;
		champ->label = ft_strdup(ft_erspace(op_param[0]));
		champ = ft_lst(sfile, champ);
		return (ft_check(rop_param[0], rop_param[1], champ));
	}
	else
		return (ft_check(op_param[0], op_param[1], champ));
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
			if (!ft_precheck(op_param, champ, sfile))
				err = 1;
			ft_free_strtab(op_param);
		}
		i++;
		free(line);
	}
	free(line);
	if (ret == -1 || err == 1)
		return (0);
	return (1);
}

int			ft_asm(t_asm *sfile, t_champ *champ)
{
	if (!ft_parse(sfile, champ))
	{
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
