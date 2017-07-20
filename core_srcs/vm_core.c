/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/20 14:26:55 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	kill_proc(void *e)
{
	t_proc *proc;
	int	tmp;

	proc = (t_proc*)(e);
	tmp = proc->live_in_ctd;
	proc->live_in_ctd = 0;
	return (tmp);
}

static void	free_proc(void *e, size_t size)
{
	(void)size;
	ft_memdel(&e);
}

static int	vm_rules(t_vm *vm)
{
	if (vm->ctd_cycle == vm->ctd)
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
		ft_lstdelif(&(vm->procs), free_proc, kill_proc);
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
		if (!proc->exec_in)
		{
			if (parse_pcb_n_param(vm, proc))
				op_tab[proc->op_code].f(vm, proc);
//			put_proc(elm);
			init_proc(vm, proc, proc->ipc);
//			put_proc(elm);
		}
		else
			proc->exec_in--;
		elm = elm->next;
	}
	return (1);
}

int		vm_core(t_vm *vm)
{
	nc_event_handling(vm);
	while (vm->dump != vm->cycle && vm->procs)
	{
		if (!vm->play)
			continue;
//		ft_lstiter(vm->procs, put_proc);
		put_vm_infos(vm);
		vm_rules(vm);
		vm_play(vm);
		vm->cycle++;
		vb_cycles(vm);
		vm->ctd_cycle++;
		nc_loop(vm);
	}
	put_vm_infos(vm);
	return (1);
}
