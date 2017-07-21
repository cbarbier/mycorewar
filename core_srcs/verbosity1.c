/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/21 11:43:09 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
	
int			vb_introduce(t_vm *vm)
{
	int			i;
	int			id_p;
	t_header	*h;

	if (vm->ncurse)
		return (0);
	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->nb_players)
	{
		id_p = vm->players[i].id;
		h = &(vm->players[i].header);
		ft_printf("* Player %d, weighing %d bytes, ", id_p, h->prog_size);
		ft_printf("\"%s\" (\"%s\") !\n", h->prog_name, h->comment);
		i++;
	}
	return (1);
}

int			vb_cycles(t_vm *vm)
{
	if (!(vm->verbose & 2))
		return (0);
	ft_printf("It is now cycle %d\n", vm->cycle);
	return (1);
}

int			vb_operations(t_proc *proc)
{
	(void)proc;
	return (1);
}	

int			vb_winner(t_vm *vm)
{
	t_player	*p;

	p = vm->last_player_live;
	ft_printf("Contestant %d, \"%s\", has won !\n", p->id, p->header.prog_name);
	return (1);
}
