/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sti.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/26 13:35:26 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_sti(t_vm *vm, t_proc *proc)
{
	int	reg_p0;
	int	index;
	int	index2;
	int	addr;

	if (!get_param_value(vm, proc, 0, &reg_p0)
	|| !get_param_value(vm, proc, 1, &index)
	|| !get_param_value(vm, proc, 2, &index2))
		return (0);
	if (proc->ptype[1] == T_IND)
		index = getnbytes(vm, proc->pc + m0d(index, IDX_MOD), 4, 0);
	addr = setnbytes(vm, proc->pc + m0d(index + index2, IDX_MOD), reg_p0, 4);
	if (vm->verbose & 4)
	{
		ft_printf("P%4d | sti r%d %d %d\n", proc->id,
				proc->param[0], index, index2);
		ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n",
				index, index2, index + index2, addr);
	}
	return (1);
}
