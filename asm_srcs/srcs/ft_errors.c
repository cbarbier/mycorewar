/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 11:43:41 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/08 11:44:17 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void  ft_error(t_asm *sfile)
{
	t_champ *champ;

	champ = sfile->champ;
	while (champ)
	{
		if (champ-> err == 1)
		{
			ft_printf("\033[1m\033[37m%s:%d:%d: \033[1m\033[31merror:\x1b[0m ",
					sfile->origin, champ->ligne, champ->col + 1);
			if (champ->errcode == 1)
				ft_printf(".name wrong format\n");
			else if (champ->errcode == 2)
				ft_printf(".comment wrong format\n");
			else if (champ->errcode == 3)
				ft_printf("Unknown mnemonique\n");
			else if (champ->errcode == 4)
				ft_printf("Parameter missing\n");
			else if (champ->errcode == 4)
				ft_printf("Parameters missing\n");
			else if (champ->errcode == 5)
				ft_printf("Too much parameters\n");
			else if (champ->errcode == 6)
				ft_printf("Wrong parameters\n");
			else if (champ->errcode == 7)
				ft_printf("Unknown label\n");
			ft_printf("   %s %s\n%*c\n",champ->op, champ->args, champ->col + 4,
					'^');
		}
		champ = champ->next;
	}
}
