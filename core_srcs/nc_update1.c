/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_update1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/20 14:20:00 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			nc_put_pc(t_vm *vm, t_proc *proc, int put)
{
	int 	j;
	int		i;
	int		cp;

	if (!vm->ncurse)
		return (0);
	j = proc->pc / 64;
	i = proc->pc % 64;
	if (put)
		cp = proc->cpair + 4;
	else
		cp = (int)(vm->colors[proc->pc]);
	wattron(vm->war, COLOR_PAIR(cp));
	mvwprintw(vm->war, j + 1, 3 * i + 1, "%.2x", vm->arena[proc->pc].i);	
	wattroff(vm->war, COLOR_PAIR(cp));
	return (1);
}

static int	nc_update_info(t_vm *vm)
{
	mvwprintw(vm->winfo, 5, 10, "%d", vm->cycle);
	return (1);
}

int			nc_loop(t_vm *vm)
{
	nc_update_info(vm);
	wrefresh(vm->war);
	wrefresh(vm->winfo);
	usleep(1000000 / vm->cps);
	return (1);
}

static void		*nc_event(void *arg_vm)
{
	t_vm	*vm;

	vm = (t_vm *)(arg_vm);
	while (42)
	{
		if (wgetch(vm->winfo) == ' ')
			vm->play = (vm->play ? 0 : 1);
	}
	return (0);
}

int			nc_event_handling(t_vm *vm)
{
	pthread_t		th;
	
	if (pthread_create(&th, NULL, nc_event, vm))
	{
		ft_fprintf(2, "problem while threading the events handling\n");
		exit(0);
	}
	return (1);
}
