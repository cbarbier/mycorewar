/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/18 11:33:09 by cbarbier         ###   ########.fr       */
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

static int	init_ncurse(t_vm *vm)
{
	if (!vm->ncurse)
		return (1);	
	vm->dump = -1;
	vm->verbose = 0;
	initscr();
	noecho();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	return (1);
}
int		main(int argc, char **argv)
{
	t_vm		vm;

	ft_printf("corewar in progress\n");
	if (!init_vm(&vm, argc, argv))
		ft_fprintf(2, "Error: on init_vm\n");
	if (DEBUG)
		put_arena(&vm);
	vb_introduce(&vm);
	init_ncurse(&vm);
	vm_core(&vm);
//	ft_lstiter(vm.procs, put_proc);
//	put_vm_infos(&vm);
	if (vm.dump == vm.cycle)
		put_arena(&vm);
	return (0);
}
