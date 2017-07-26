/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_lld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/26 15:42:39 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_lld(t_vm *vm, t_proc *proc)
{
	int	val;
	int	i_reg;

	if (!is_reg(proc->param[1]))
		return (0);
	i_reg = proc->param[1] - 1;
	if (!get_param_value(vm, proc, 0, &val))
		return (0);
	proc->reg[i_reg] = getnbytes(vm, proc->pc + m0d(val, MEM_SIZE), 4, 0);
	proc->carry = !proc->reg[i_reg];
	if (vm->verbose & 4)
		ft_printf("P%4d | lld %d r%d\n", proc->id, val, i_reg + 1);
	return (1);
}
