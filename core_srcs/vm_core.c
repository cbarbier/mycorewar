/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/24 18:52:15 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	kill_proc(void *arg_proc, void *arg_vm)
{
	t_proc		*proc;
	t_vm		*vm;
	int			tmp;

	proc = (t_proc*)(arg_proc);
	vm = (t_vm *)arg_vm;
	tmp = proc->alive;
	if (!tmp)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				proc->id, vm->cycle - proc->last_live_cycle , vm->ctd);
	proc->alive = 0;
	return (!tmp);
}

static void	free_proc(void *e, size_t size)
{
	(void)size;
	ft_memdel(&e);
}

static int	vm_rules(t_vm *vm)
{
	if (vm->ctd_cycle >= vm->ctd)
	{
		if (vm->live_in_ctd > NBR_LIVE || vm->check == MAX_CHECKS)
		{
			vm->ctd -= CYCLE_DELTA;
			vm->check = 0;
		}
		else
			vm->check++;
		vm->ctd_cycle = 0;
		//kill the one that did not execute live;
		// and reset proc->live_in_ctd;
		ft_lstfilter(&(vm->procs), free_proc, kill_proc, vm);
	}
	return (1);
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
			if (parse_pcb_n_param(vm, proc))
				op_tab[proc->op_code].f(vm, proc);
//			put_proc(elm);
			vb_pc_movement(vm, proc);
			init_proc(vm, proc, proc->ipc);
//			put_proc(elm);
		}
		elm = elm->next;
	}
	return (1);
}

int		vm_core(t_vm *vm)
{
	nc_event_handling(vm);
	while (vm->dump != vm->cycle && vm->procs)
	{
		if (vm->ncurse && (!vm->play || vm->step == vm->cycle))
			continue;
		vm->ctd_cycle++;
		vm->cycle++;
		vb_cycles(vm);
//		ft_lstiter(vm->procs, put_proc);
//		put_vm_infos(vm);
		vm_rules(vm);
		vm_play(vm);
		nc_loop(vm);
	}
	vb_winner(vm);
	vm->play = -1; //to stop thread for event handling
	put_vm_infos(vm);
	return (1);
}
