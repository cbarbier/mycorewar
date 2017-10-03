/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 16:31:11 by fmaury            #+#    #+#             */
/*   Updated: 2017/10/03 17:11:55 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_tab[17];

int		ft_rev_find_op(int op)
{
	int		i;
	i = 0;
	while (g_tab[i])
	{
		if (g_tab[i] == op)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_fill_paramt_asm *sfile, int i)
{
	sfile->code >>= 8;
}

void	ft_reverse_code(t_asm *sfile)
{
	char	*str;

	str = sfile->bin + (16 + PROG_NAME_LENGTH + COMMENT_LENGTH);
	ft_printf("str:%x\n",str[0]);
	sfile->code = ft_strjoinzfree(sfile->code, g_tab[i].param);
	if (g_tab[i].ocod)
		ft_fill_param(sfile, i);
}
