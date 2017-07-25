/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_ld.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/25 17:36:56 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_ld(t_vm *vm, t_proc *proc)
{
	int	val;
	int	i_reg;

	if (!is_reg(proc->param[1]))
		return (0);
	i_reg = proc->param[1] - 1;
	if (!get_param_value(vm, proc, 0, &val))
		return (0);
	if (proc->ptype[0] == T_IND)
		val = getnbytes(vm, proc->pc + val, 4);
	proc->reg[i_reg] = val;
	proc->carry = !proc->reg[i_reg];
	return (1);
}
