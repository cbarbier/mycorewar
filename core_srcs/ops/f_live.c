/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_live.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/07 18:56:16 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		vb_operation_live(t_vm *vm, t_proc *proc, int id)
{
	if (!(vm->verbose & 4))
		return (0);
	ft_printf("P%4d | live %d\n", proc->id, id);
	return (1);
}

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

static	void	pt_blks(t_vm *vm, t_list *blks)
{
	t_blk *e;

	ft_printf("-----------------------------\n");
	while (blks)
	{
		e = (t_blk*)blks->content;
		ft_printf("i %d j %d unitl %d   cl : %d\n",
				e->i, e->j, e->until, vm->cycle);
		blks = blks->next;
	}
	ft_printf("-----------------------------\n");
}

int				f_live(t_vm *vm, t_proc *proc)
{
	int			id;
	t_player	*pl;

	id = proc->param[0];
	pl = get_player_by_id(vm, id);
	if (pl)
	{
		make_it_blink(vm, proc);
		if (!vm->ncurse)
			pt_blks(vm, vm->blinks);
		vm->last_player_live = pl;
		pl->last_live_cycle = vm->cycle;
		proc->last_live_cycle = vm->cycle;
		pl->live_in_ctd++;
		proc->alive++;
		vm->live_in_ctd++;
	}
	vb_operation_live(vm, proc, id);
	if (pl && (vm->verbose & 1))
		ft_printf("Player %d (%s) is said to be alive\n",
				pl->id, pl->header.prog_name);
	return (1);
}
