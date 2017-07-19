/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/19 19:55:00 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		nc_init_info(t_vm *vm)
{
	mvwprintw(vm->winfo, 3, 3, "COREWAR");
	mvwprintw(vm->winfo, 4, 3, "by team Dinosaurus");
	mvwprintw(vm->winfo, 5, 3, "Cycle: %d", vm->cycle);
	wrefresh(vm->winfo);
	return (1);
}
