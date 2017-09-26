/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:48:53 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/26 18:45:54 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_aff(t_asm *sfile, t_champ *champ)
{
	int		size;
	int		i;

	size = 0;
	ft_printf("Progam size: %d bytes\nName: %s\nComment: %s\n\n", ft_total_size(champ), 
			sfile->name, sfile->comment);
	while (champ)
	{
		i = 0;
		if (champ->lab)
			ft_printf("%d	   :	%s\n", size, champ->label);
		else if (champ->instr)
		{
			ft_printf("%d	(%d):		%s\n", size, ft_size(champ), champ->op);
			while (champ->arg[i])
			{
				ft_printf("\t%s", champ->arg[i]);
				i++;
			}
			ft_putchar('\n');
		}
		size += ft_size(champ);
		champ = champ->next;
	}
}
