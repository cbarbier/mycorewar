/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_head.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 11:44:23 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/08 11:44:46 by fmaury           ###   ########.fr       */
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

int		ft_head(t_asm *sfile)
{
	int		i;
	int		ret;
	char	**tab;
	char	*line;

	i = 0;
	while (i < 2 && (ret = get_next_line(sfile->fd, &line) > 0))
	{
		tab = ft_strsplitnbif(line, ft_isspace, 1);
		if (i == 0)
		{
			if (ft_strcmp(tab[0], ".name") == 0)
				sfile->name = ft_strdup(ft_erase_dc(tab[1]));
			else
				return (0);
		}
		else
		{
			if (ft_strcmp(tab[0], ".comment") == 0)
				sfile->comment = ft_strdup(ft_erase_dc(line + 9));
			else
				return (0);
		}
		free(line);
		i++;
	}
	ft_set_header(sfile);
	return (1);
}
