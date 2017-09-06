/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr33.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/06 14:58:51 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		free_proc(void *e, size_t size)
{
	(void)size;
	ft_memdel(&e);
}

int			free_vm(t_vm *vm)
{
	ft_lstdel(&(vm->procs), free_proc);
	if (vm->ncurse)
		endwin();
	return (1);
}
