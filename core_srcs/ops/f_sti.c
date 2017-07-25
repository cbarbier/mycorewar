/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sti.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/25 17:48:36 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_sti(t_vm *vm, t_proc *proc)
{
	int	reg_p0;
	int	index;
	int	index2;

	if (!get_param_value(vm, proc, 0, &reg_p0)
	|| !get_param_value(vm, proc, 1, &index)
	|| !get_param_value(vm, proc, 2, &index2))
		return (0);
	if (proc->ptype[1] == T_IND)
		index = getnbytes(vm, proc->pc + index, 4);
	index = (index + index2) % IDX_MOD;
	setnbytes(vm, proc->pc + index, reg_p0, 4);
	return (1);
}
