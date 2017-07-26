/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_zjmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/26 13:01:23 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_zjmp(t_vm *vm, t_proc *proc)
{
	int	p0;

	if (!get_param_value(vm, proc, 0, &p0))
		return (0);
	if (proc->carry)
	{
		proc->ipc = (proc->pc + m0d(p0, IDX_MOD));
		if (proc->ipc < 0)
			proc->ipc += MEM_SIZE;
		else
			proc->ipc %= MEM_SIZE;
	}
	else
		proc->ipc = (proc->pc + 3) % MEM_SIZE;
	if (vm->verbose & 4)
		ft_printf("p%4d | zjmp  %d %s\n",
				proc->id, p0, (proc->carry ? "OK" : "FAILED"));
	return (1);
}
