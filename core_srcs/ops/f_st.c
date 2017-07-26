/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_st.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/26 15:43:56 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_st(t_vm *vm, t_proc *proc)
{
	int	reg_p0;
	int	index;

	if (!get_param_value(vm, proc, 0, &reg_p0)
	|| !get_param_value(vm, proc, 1, &index))
		return (0);
	setnbytes(vm, proc->pc + m0d(index, IDX_MOD), reg_p0, 4);
	if (vm->verbose & 4)
		ft_printf("P%4d | st r%d %d\n", proc->id, proc->param[0], index);
	return (1);
}
