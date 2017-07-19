/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/19 14:07:46 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
	
int	vb_introduce(t_vm *vm)
{
	int		i;
	t_header	*h;

	if (vm->ncurse)
		return (0);
	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->nb_players)
	{
		h = &(vm->players[i].header);
		ft_printf("* Player %d, weighing %d bytes, ", i + 1, h->prog_size);
		ft_printf("\"%s\" (\"%s\") !\n", h->prog_name, h->comment);
		i++;
	}
	return (1);
}

int	vb_cycles(t_vm *vm)
{
	if (!(vm->verbose & 2))
		return (0);
	ft_printf("It is now cycle %d\n", vm->cycle);
	return (1);
}

int	vb_operations(t_proc *proc)
{
	(void)proc;
	return (1);
}	
