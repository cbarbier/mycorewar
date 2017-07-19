/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/19 15:23:16 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
	
static int	put_arena(t_vm *vm)
{
	int		i;
	int		j;

	j = 0;
	while(j < 64)
	{
		ft_printf("0x%.4x :", j * 64);
		i = 0;
		while (i < 64)
			ft_printf(" %.2x", vm->arena[64 * j + i++].i);
		j++;
		ft_printf("\n");
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_vm		vm;

	ft_printf("corewar in progress\n");
	if (!init_vm(&vm, argc, argv))
		ft_fprintf(2, "Error: on init_vm\n");
	if (DEBUG && !vm.ncurse)
		put_arena(&vm);
	vb_introduce(&vm);
	nc_init(&vm);
	vm_core(&vm);
//	ft_lstiter(vm.procs, put_proc);
//	put_vm_infos(&vm);
	if (vm.dump == vm.cycle)
		put_arena(&vm);
	return (0);
}
