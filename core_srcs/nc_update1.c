/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_update1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/07 16:50:58 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			nc_put_pc(t_vm *vm, t_proc *proc, int put)
{
	int		j;
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
	int		j;
	int		i;
	int		cp;

	mvwprintw(vm->winfo, 5, 10, "%d", vm->cycle);
	j = 10;
	i = -1;
	mvwprintw(vm->winfo, 7, 14, "%d", ft_lstlen(vm->procs));
	while (++i < vm->nb_players)
	{
		cp = vm->last_player_live == vm->players + i ? i + 5 : i + 1;
		wattron(vm->winfo, COLOR_PAIR(cp));
		mvwprintw(vm->winfo, j, 18, "%d", vm->players[i].last_live_cycle);
		mvwprintw(vm->winfo, j + 1, 18, "%d", vm->players[i].live_in_ctd);
		j += 4;
	}
	wattron(vm->winfo, COLOR_PAIR(10));
	mvwprintw(vm->winfo, j, 18, "% 10d", vm->ctd);
	return (1);
}

int			nc_loop(t_vm *vm)
{
	if (!vm->ncurse)
		return (0);
	nc_update_info(vm);
	wrefresh(vm->war);
	wrefresh(vm->winfo);
	usleep(1000000 / vm->cps);
	return (1);
}

static void	nc_winner_helper(t_vm *vm, t_player *p, int i)
{
	mvwprintw(vm->war, i - 2, 50,
			"                                 			");
	mvwprintw(vm->war, i - 1, 50,
			"                              			    ");
	mvwprintw(vm->war, i, 50,
			"                    			            ",
			p->header.prog_name);
	mvwprintw(vm->war, i, 50,
			"   THE WINNER IS %.10s", p->header.prog_name);
	mvwprintw(vm->war, i + 1, 50,
			"                    	                    ");
	mvwprintw(vm->war, i + 2, 50,
			"                    		            	");
	mvwprintw(vm->war, i + 3, 50,
			"press ESC to quit.                         ");
	mvwprintw(vm->war, i + 4, 50,
			"                 created by TEAM Dinosaurus");
}

int			nc_winner(t_vm *vm)
{
	t_player	*p;
	int			i;

	if (!vm->ncurse)
		return (0);
	i = 30;
	p = vm->last_player_live;
	init_pair(11, COLOR_BLACK, COLOR_MAGENTA);
	wattron(vm->war, COLOR_PAIR(11));
	nc_winner_helper(vm, p, i);
	wattroff(vm->war, COLOR_PAIR(1));
	wrefresh(vm->war);
	wgetch(vm->war);
	return (1);
}
