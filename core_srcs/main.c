/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/20 17:47:03 by cbarbier         ###   ########.fr       */
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
	{
		ft_fprintf(2, "Error: on init_vm\n");
		put_usage(argv);
	}
	if (DEBUG && !vm.ncurse)
		put_arena(&vm);
	vb_introduce(&vm);
	nc_init(&vm);
	vm_core(&vm);
	if (vm.dump == vm.cycle)
		put_arena(&vm);
	return (0);
}

int		put_usage(char **argv)
{
	ft_fprintf(2, "Usage: {red}%s{no} [-d N -v N -ncurse] \
 < [-n N] champion1.cor> <...>\n", argv[0]);
	ft_fprintf(2, "#### TEXT OUTPUT MODE #####################################\
#####################\n\
    -{grn}d{no} N  : Dumps memory after N cycles then exits\n\
    -{grn}v{no} N  : Verbosity levels, can be added together to enable several\n\
    -{grn}n{no} N  : Gives the given id to the following champ (file .cor)\n\
	 - {yel}0{no}  : Show only essentials\n\
	 - {yel}1{no}  : Show lives\n\
	 - {yel}2{no}  : Show cycles\n\
	 - {yel}4{no}  : Show operations (Params are NOT litteral ...)\n\
	 - {yel}8{no}  : Show deaths\n\
	 - {yel}16{no} : Show PC movements (Except for jumps)\n");
	ft_fprintf(2, "#### NCURSES OUTPUT MODE ###################################\
#####################\n\
    -{blu}ncurse{no} : Ncurses output mode with some nice features\n");
	return (1);
}
