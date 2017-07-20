/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/20 16:06:24 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	load_prog(t_vm *vm, t_player *p, int ip)
{
	int	index;

	index = ip * MEM_SIZE / vm->nb_players;
	ft_memcpy(vm->arena + index, p->prog, p->header.prog_size);
	return (1);
}

static int	add_process(t_vm *vm, t_player *p, int pc)
{
	static int	id_proc = 1;
	t_proc		proc;
	t_list		*elm;

	ft_bzero(&proc, sizeof(t_proc));
	proc.id = id_proc;
	proc.cpair = id_proc++;
	proc.reg[0] = p->id;
	proc.pc = pc;
	proc.player_id = p->id;
	if (!(elm = ft_lstnew(&proc, sizeof(t_proc))))
		return (0);
	ft_lstadd(&(vm->procs), elm);
	return (1);
}

int		init_vm(t_vm *vm, int argc, char **argv)
{
	int		ip;
	int		pc;

	ft_bzero(vm, sizeof(t_vm));
	vm->dump = -1;
	if (!parse_argv(vm, argc, argv))
		return (0);
	vm->ctd = CYCLE_TO_DIE;
	vm->cps = 50;
	vm->step = -2;
	ft_printf("parse argv ok! nb players: %d\n", vm->nb_players);
	ip = 0;
	while (ip < vm->nb_players)
	{
		if (!parse_player(vm->players + ip))
		{
			ft_printf("parse player %d failed\n", ip);
			return (0);
		}
		pc = ip * MEM_SIZE / vm->nb_players;
		load_prog(vm, vm->players + ip, ip);
		add_process(vm, vm->players + ip, pc);
		init_proc(vm, (t_proc*)(vm->procs->content), pc);
		ip++;
	}
	return (1);
}
