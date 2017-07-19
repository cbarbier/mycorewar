/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_init1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/19 19:57:52 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	nc_init_colors(t_vm *vm)
{
	t_list 	*elm;
	t_proc	 *p;
	int		i;

	i = vm->nb_players;
	elm = vm->procs;
	ft_memset(vm->colors, 9, MEM_SIZE);
	while (elm)
	{
		p = (t_proc*)(elm->content);
		ft_memset(vm->colors + p->pc, p->cpair, (int)(vm->players[--i].header.prog_size));
		elm = elm->next;
	}
	return (1);
}

static int	nc_init_pc(t_vm *vm)
{
	t_list		*elm;
	t_proc		*p;

	elm = vm->procs;
	while (elm)
	{
		p = (t_proc*)(elm->content);
		nc_put_pc(vm, p, 1);
		elm = elm->next;
	}
	return (1);
}

static int	nc_init_arena(t_vm *vm)
{
	int		i;
	int		j;

	nc_init_colors(vm);
	j = 0;
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			wattron(vm->war, COLOR_PAIR((int)(vm->colors[j * 64 + i])));
			mvwprintw(vm->war, j + 1, 3 * i + 1, "%.2x", vm->arena[j * 64 + i].i);
			wattroff(vm->war, COLOR_PAIR((int)(vm->colors[j * 64 + i])));
			i++;
		}
		j++;
	}
	nc_init_pc(vm);
	wrefresh(vm->win);
	wrefresh(vm->war);
	nc_init_info(vm);
//	while (42);
	return (1);
}

static int	nc_init_win(t_vm *vm)
{
	vm->win = newwin(68, 260, 0, 0);
	vm->war = newwin(66, 190, 1, 2);
	vm->winfo = newwin(68, 67, 0, 193);
	wattron(vm->win, COLOR_PAIR(10));
	wattron(vm->winfo, COLOR_PAIR(10));
	wborder(vm->win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 
	wborder(vm->winfo, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 	
	return (nc_init_arena(vm));
}

int			nc_init(t_vm *vm)
{
	if (!vm->ncurse)
		return (1);	
	ft_printf("ncurse initializing\n");
	vm->dump = -1; //ncurse overright dump
	vm->verbose = 0;// and verbose
	initscr();
	curs_set(0);
	noecho();
	start_color();
	init_color(COLOR_YELLOW, 420, 420, 420);
	assume_default_colors(COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	init_pair(9, COLOR_YELLOW, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_YELLOW);
	return (nc_init_win(vm));
}
