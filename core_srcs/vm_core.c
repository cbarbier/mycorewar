/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/25 13:28:33 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	reset_players_live(t_vm *vm, int nb_pl)
{
	while (nb_pl--)
		vm->players[nb_pl].live_in_ctd = 0;
}

static int	kill_proc(void *arg_proc, void *arg_vm)
{
	t_proc		*proc;
	t_vm		*vm;
	int			tmp;

	proc = (t_proc*)(arg_proc);
	vm = (t_vm *)arg_vm;
	tmp = proc->alive;
	if ((vm->ctd <= 0 || !tmp) && (vm->verbose & 8))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		proc->id, vm->cycle - proc->last_live_cycle, vm->ctd);
	proc->alive = 0;
	if (vm->ctd <= 0)
		return (1);
	return (!tmp);
}

static int	vm_rules(t_vm *vm)
{
	if (vm->ctd_cycle == vm->ctd || vm->ctd <= 0)
	{
		//ft_printf("ctd_cycle %d, ctd %d   ", vm->ctd_cycle, vm->ctd);
		ft_lstfilter(&(vm->procs), free_proc, kill_proc, vm);
		if (vm->live_in_ctd >= NBR_LIVE || vm->check == MAX_CHECKS - 1)
		{
			vm->ctd -= CYCLE_DELTA;
			vm->check = 0;
			if (vm->verbose & 2)
				ft_printf("Cycle to die is now %d\n", vm->ctd);
		}
		else
			vm->check++;
		vm->live_in_ctd = 0;
		vm->ctd_cycle = 0;
		reset_players_live(vm, vm->nb_players);
	}
	return (vm->procs ? 1 : 0);
}

static int	vm_play(t_vm *vm)
{
	t_list	*elm;
	t_proc	*proc;

	elm = vm->procs;
	while (elm)
	{
		proc = (t_proc*)(elm->content);
		if (!--proc->exec_in)
		{
			if (proc->op_code != -1)
			{
				g_tab[proc->op_code].f(vm, proc);
				vb_pc_movement(vm, proc);
			}
			init_proc(vm, proc, proc->ipc);
		}
		elm = elm->next;
	}
	return (1);
}

int			vm_core(t_vm *vm)
{
	while (!vm->quit && vm->dump != vm->cycle && vm->procs)
	{
		nc_event_handling(vm);
		if (vm->ncurse && (!vm->play || vm->step == vm->cycle))
			continue;
		vm->cycle++;
		vm->ctd_cycle++;
		vb_cycles(vm);
//		put_vm_infos(vm);
		if (vm->cycle == -1)
			ft_lstany(vm->procs, put_proc, 0);
		vm_play(vm);
		vm_rules(vm);
		ft_lstfilter(&(vm->blinks), free_blk, reset_blk, vm);
		nc_loop(vm);
	}
	vm->play = -1; //to stop thread for event handling
	return (1);
}
