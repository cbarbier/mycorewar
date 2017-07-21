/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_live.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/21 11:10:49 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player	*get_player_by_id(t_vm *vm, int id)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i].id == id)
			return (vm->players + i);
		i++;
	}
	return (0);
}

int				f_live(t_vm *vm, t_proc *proc)
{
	int		id;
	t_player	*pl;

	id = proc->param[0];
	if (!(pl = get_player_by_id(vm, id)))
		return (1);	
	vm->last_player_live = pl;
	pl->last_live_cycle = vm->cycle;
	proc->live_in_ctd++;	
	vm->live_in_ctd++;
	if (vm->verbose & 1)
		ft_printf("Player %d (%s) is said to be alive\n", 
				pl->id, pl->header.prog_name);
	return (1);
}
