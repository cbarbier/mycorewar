/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/12 19:21:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_core(t_vm *vm)
{
	t_list	*elm;
	t_proc	*proc;

	elm = vm->procs;
	while (elm)
	{
		proc = (t_proc*)(elm->content);
		if (init_proc(vm, proc))
		{
			ft_printf("init_proc ok\n");
			if (parse_pcb(vm, proc))
				ft_printf("parse_pcb ok\n");
			else
				ft_printf("parse_pcb ko\n");
		}
		else
			ft_printf("init_proc ko\n");
		put_proc(elm);
		elm = elm->next;
	}
	return (1);
}
