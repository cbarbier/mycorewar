/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_reg(int reg)
{
	if (reg < 1 || reg > 17)
		return (0);
	return (1);
}

int		getnbytes(t_vm *vm, int addr, int n)
{
	int	i;
	int	val;
	int	tmp;

	i = 0;
	val = 0;
	while (i < n)
	{
		tmp = (addr + i) % MEM_SIZE;
		val = (val << 8) + vm->arena[tmp].i;
		i++;
	}
	return (val);
}

int		inc_pc(t_proc *proc, int n)
{
	proc->ipc = (proc->ipc + n) % MEM_SIZE;
	return (1);
}
