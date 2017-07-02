/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
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

static int	add_process(t_vm *vm, t_player *p, int ip)
{
	static int	id_proc;
	t_proc		proc;
	t_list		*elm;

	ft_bzero(&proc, sizeof(t_proc));
	proc.id = id_proc++;
	proc.reg[0] = p->id;
	proc.pc = ip * MEM_SIZE / vm->nb_players;
	if (!(elm = ft_lstnew(&proc, sizeof(t_proc))))
		return (0);
	ft_lstadd(&(vm->procs), elm);
	return (1);
}

int		init_vm(t_vm *vm, int argc, char **argv)
{
	int		ip;

	ft_bzero(vm, sizeof(t_vm));
	if (!parse_argv(vm, argc, argv))
		return (0);
	ft_printf("parse argv ok!\n");
	ip = 0;
	while (ip < vm->nb_players)
	{
		if (!parse_player(vm->players + ip))
		{
			ft_printf("parse player %d failed\n", ip);
			return (0);
		}
		load_prog(vm, vm->players + ip, ip);
		add_process(vm, vm->players + ip, ip);
		ip++;
	}
	return (1);
}
