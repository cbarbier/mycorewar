/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_xor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/05 10:58:35 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_xor(t_vm *vm, t_proc *proc)
{
	int	p0;
	int	p1;
	int	i_reg;

	if (!get_param_value(vm, proc, 0, &p0)
	|| !get_param_value(vm, proc, 1, &p1)
	|| !is_reg(proc->param[2]))
		return (0);
	i_reg = proc->param[2] - 1;
	proc->reg[i_reg] = p0 ^ p1;
	proc->carry = !(proc->reg[i_reg]);
	if (vm->verbose & 4)
		ft_printf("p%4d | xor r%d r%d r%d\n", proc->id,
				proc->param[0], proc->param[1], i_reg + 1);
	return (1);
}
