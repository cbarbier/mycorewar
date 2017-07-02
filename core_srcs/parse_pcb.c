/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pcb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		init_proc(t_vm *vm, t_proc *proc)
{
	ft_bzero(proc->param, 3 * sizeof(int));
	ft_bzero(proc->psize, 3 * sizeof(int));
	ft_bzero(proc->ptype, 3 * sizeof(int));
	proc->op_code = vm->arena[proc->pc].i;
	proc->adv = 1;
	if (!(proc->op_code > 0 && proc->op_code < 17))
	{
		proc->op_code = 0;
		return (0);
	}
	proc->op_code--;
	proc->exec_in = op_tab[proc->op_code].cycle_to_wait;
	if (op_tab[proc->op_code].pcb)
		proc->adv = 2;
	return (1);
}

static int	set_types(t_proc *proc, int i, int type_code)
{
	if (type_code == REG_CODE
	&& (op_tab[proc->op_code].param[i] & T_REG))
	{
		proc->ptype[i] = T_REG;
		proc->psize[i] = 1;
	}
	else if (type_code == IND_CODE
	&& (op_tab[proc->op_code].param[i] & T_IND))
	{
		proc->ptype[i] = T_IND;
		proc->psize[i] = IND_SIZE; 
	}
	else if (type_code == DIR_CODE
	&& (op_tab[proc->op_code].param[i] & T_DIR))
	{
		proc->ptype[i] = T_DIR;
		proc->psize[i] = op_tab[proc->op_code].var ? 2 : 4;
	}
	else
		return (0);
	return (1);
}

static int	get_param(t_vm *vm, t_proc *proc, int i, int t)
{
	int	i_b;
	int	val;
	int	tmp;

	if (!set_types(proc, i, t))
		return (0);
	ft_printf("size of param %d\n", proc->psize[i]);
	i_b = 0;
	val = 0;
	while (i_b < proc->psize[i]) 
	{
		proc->ipc = (proc->ipc + 1) % MEM_SIZE;
		tmp = vm->arena[proc->ipc].i;
		ft_printf("tmp %.2x ", tmp);
		val = (val << 8) + tmp;
		i_b++;
	}
	ft_printf("\n");
	proc->param[i] = val;
	return (1);
}
	
int		parse_pcb(t_vm *vm, t_proc *proc)
{
	int		pcb;
	int		i;
	int		t;
	int		res;

	proc->ipc = (proc->pc + 1) % MEM_SIZE;
	pcb = vm->arena[proc->ipc].i;
	i = 0;
	res = 1;
	ft_printf("{red}%b{no}\n", pcb);
	ft_printf("{grn}%b{no}\n", 0xa4);
	while (i < op_tab[proc->op_code].nb_params)
	{
		t = (pcb >> (6 - 2 * i)) & 0x03;
		ft_printf("pcb p%d %.2b\n", i, t);
		if (!(t | op_tab[proc->op_code].param[i]))
			res = 0;
		proc->adv += get_param(vm, proc, i, t);
		i++;
	}
	return (res);
}
