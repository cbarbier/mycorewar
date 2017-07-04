/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		f_fork(t_vm *vm, t_proc *proc)
{
	t_list	*elm;
	int		p0;
	t_proc		*new;
	int		id;

	if (!get_param_value(vm, proc, 0, &p0)
	|| !(elm = ft_lstnew(proc, sizeof(t_proc))))
		return (0);
	id = ((t_proc*)(vm->procs->content))->id + 1;
	ft_lstadd(&(vm->procs), elm);
	new = (t_proc*)(vm->procs->content);
	new->pc = (proc->pc + p0) % MEM_SIZE;
	return (1);
}
