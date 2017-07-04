/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_zjmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_zjmp(t_vm *vm, t_proc *proc)
{
	int	p0;

	if (!get_param_value(vm, proc, 0, &p0))
		return (0);
	if (proc->carry)
		proc->ipc = (proc->pc + p0) % MEM_SIZE;
	else
		proc->ipc = (proc->pc + 3) % MEM_SIZE;
	return (1);
}
