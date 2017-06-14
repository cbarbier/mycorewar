/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:12:45 by cbarbier          #+#    #+#             */
/*   Updated: 2017/04/27 17:25:37 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/includes/libft.h"
# define DEBUG		1

typedef struct	s_proc
{
	int		id;
	unsigned char	regs[REG_NUMBER * REG_SIZE];
	unsigned char	pc[REG_SIZE];
	char		carry;
}		t_proc;

typedef struct	s_player
{
	int	id;
	char	is_alive;
	int	live_in_ctd; // nb live by player in this cycle to die
	t_list	*proces; // list of processus for each player
}		t_player;	

typedef struct	s_vm
{
	t_player 	players[MAX_PLAYER];
	int		nb_players;
	unsigned char	arena[MEM_SIZE];
	int		cycle;
	int		check;
	int		ctd; //cycle to die
	int		dump; //arg --dump 
}		t_vm;

#endif
