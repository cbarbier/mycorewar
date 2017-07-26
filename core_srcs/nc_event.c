/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/26 15:25:03 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		nc_update_cps(t_vm *vm, int key, int *p_cps)
{
	int		cps;

	cps = *p_cps;
	if (key == 'q' && cps - 10 > 0)
		*p_cps = cps - 10;
	else if (key == 'w' && cps - 1 > 0)
		*p_cps = cps - 1;
	else if (key == 'e' && cps + 1 <= 1000)
		*p_cps = cps + 1;
	else if (key == 'r' && cps + 10 < 1000)
		*p_cps = cps + 10;
	mvwprintw(vm->winfo, 17 + 4 * vm->nb_players, 18, "% 10d", vm->cps);
	return (1);
}

static void		*nc_event(void *arg_vm)
{
	t_vm			*vm;
	int				key;

	vm = (t_vm *)(arg_vm);
	while (vm->play != -1)
	{
		key = wgetch(vm->winfo);
		if (key == ' ')
		{
			vm->play = (vm->play && vm->step != vm->cycle ? 0 : 1);
			vm->step = -1;
		}
		else if (ft_strchr("qwer", key))
		{
			nc_update_cps(vm, key, &(vm->cps));
			wrefresh(vm->winfo);
		}
		else if (key == 's' && (vm->play = 1))
			vm->step = vm->cycle + 1;
	}
	return (0);
}

int				nc_event_handling(t_vm *vm)
{
	pthread_t		th;

	if (!vm->ncurse)
		return (0);
	if (pthread_create(&th, NULL, nc_event, vm))
	{
		ft_fprintf(2, "problem while threading the events handling\n");
		exit(0);
	}
	return (1);
}
