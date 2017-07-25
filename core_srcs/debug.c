/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:17:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/25 12:12:10 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		put_vm_infos(t_vm *vm)
{
	int	i;

	if (vm->ncurse || !DEBUG)
		return (0);
	ft_printf("-----------------------------------\n");
	ft_printf("|               VM                |\n");
	ft_printf("-----------------------------------\n");
	ft_printf("| nb_players % 21.7d|\n", vm->nb_players);
	ft_printf("| dump       % 21.7d|\n", vm->dump);
	ft_printf("| verbose    % 21.7d|\n", vm->verbose);
	ft_printf("| ncurse     % 21.7d|\n", vm->ncurse);
	ft_printf("| check      % 21.7d|\n", vm->check);
	ft_printf("| cycle      % 21.7d|\n", vm->cycle);
	ft_printf("| ctd        % 21.7d|\n", vm->ctd);
	ft_printf("| cycle in ctd % 19.7d|\n", vm->ctd_cycle);
	ft_printf("| live in ctd  % 19.7d|\n", vm->live_in_ctd);
	ft_printf("-----------------------------------\n");
	ft_printf("| PLAYERS                         |\n");
	i = -1;
	while (++i <vm->nb_players)
		ft_printf("|       id % 8d fd % 8d   |\n", vm->players[i].id, vm->players[i].fd);
	ft_printf("-----------------------------------\n\n");
	return (1);
}
	
void		put_proc(t_list *e)
{
	t_proc	*p;
	int	i;

	if (!DEBUG)
		return ;
	p = (t_proc*)(e->content);
	ft_printf("-----------------------------------\n");
	ft_printf("|           PROC % 6d           |\n", p->id);
	ft_printf("-----------------------------------\n");
	ft_printf("|op_code     % 21.7d|\n", p->op_code);
	ft_printf("|pc                         0x%.4x|\n", p->pc);
	ft_printf("|ipc                        0x%.4x|\n", p->ipc);
	ft_printf("|adv         % 21.7d|\n", p->adv);
	ft_printf("|carry       % 21.7d|\n", p->carry);
	ft_printf("|error pcb   % 21.7d|\n", p->error_pcb);
	ft_printf("|exec_in     % 21.7d|\n", p->exec_in);
	ft_printf("-----------------------------------\n");
	i = -1;
	ft_printf("| PARAMS |  T  |  S  |     VAL    |\n");
	ft_printf("-----------------------------------\n");
	while (++i < 3 && p->psize[i])
		ft_printf("| %.1d      | %.2d  |  %.1d  |    % 8d|\n", i, p->ptype[i], p->psize[i], p->param[i]);
	ft_printf("-----------------------------------\n");
}

int		put_regs(t_proc *p)
{
	int			i;

	i = 0;
	ft_printf("REGS of PROCESS %d\n", p->id);
	while (i < REG_NUMBER)
	{
		ft_printf("r%d : %d\n", i + 1, p->reg[i]);
		i++;
	}
	return (1);
}
