/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:12:45 by cbarbier          #+#    #+#             */
/*   Updated: 2017/06/14 17:25:37 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "../libft/includes/libft.h"
# include "op.h"
# include <ncurses.h>
# define DEBUG		0

typedef union	u_byte
{
	unsigned char	c;
	uint8_t		i;
}		t_byte;
typedef struct	s_proc
{
	int		id;
	int		player_id;
	int		reg[REG_NUMBER];
	int		pc;
	int		ipc;
	int		carry;
	int		live_in_ctd;
	int		op_code;
	int		exec_in;
	int		adv;
	int		error_pcb;
	int		ptype[3];
	int		psize[3];
	int		param[3];
}		t_proc;

typedef struct	s_player
{
	int	id;
	int	fd;
	int	live_in_ctd; // nb live by player in this cycle to die
	int	last_live_cycle;
	t_header	header;
	unsigned char	prog[CHAMP_MAX_SIZE + 2];
}		t_player;	

typedef struct	s_vm
{
	t_player 	players[MAX_PLAYERS];
	int		nb_players;
	t_byte		arena[MEM_SIZE];
	t_list		*procs; // list of processus
	int		live_in_ctd;
	int		last_player_live;
	int		cycle;
	int		check;
	int		ctd; //cycle to die
	int		ctd_cycle;
	int		dump;
	int		verbose;
	int		ncurse;
}		t_vm;
typedef union	u_mem
{
	uint8_t i[4];
	char 	c[4];
}		t_mem;

extern const t_op	op_tab[17];

int		parse_argv(t_vm *vm, int argc, char **argv);
int		parse_player(t_player *p);
int		parse_pcb_n_param(t_vm *vm, t_proc *proc);
int		init_vm(t_vm *vm, int argc, char **argv);
int		init_proc(t_vm *vm, t_proc *proc, int pc);
int		vm_core(t_vm *vm);
int		is_reg(int reg);
int		inc_pc(t_proc *proc, int n);
int		getnbytes(t_vm *vm, int addr, int n);
int		setnbytes(t_vm *vm, int addr, int val, int n);
int		get_param_value(t_vm *vm, t_proc *proc, int i, int *val);
/*
** 	INSTRUCTIONS FUNCTIONS
*/
int		f_live(t_vm *vm, t_proc *proc);
int		f_ld(t_vm *vm, t_proc *proc);
int		f_st(t_vm *vm, t_proc *proc);
int		f_add(t_vm *vm, t_proc *proc);
int		f_sub(t_vm *vm, t_proc *proc);
int		f_and(t_vm *vm, t_proc *proc);
int		f_or(t_vm *vm, t_proc *proc);
int		f_xor(t_vm *vm, t_proc *proc);
int		f_zjmp(t_vm *vm, t_proc *proc);
int		f_ldi(t_vm *vm, t_proc *proc);
int		f_sti(t_vm *vm, t_proc *proc);
int		f_fork(t_vm *vm, t_proc *proc);
int		f_lld(t_vm *vm, t_proc *proc);
int		f_lldi(t_vm *vm, t_proc *proc);
int		f_lfork(t_vm *vm, t_proc *proc);
int		f_aff(t_vm *vm, t_proc *proc);

/*
** 	DEBUG FUNCTIONS
*/
int		put_vm_infos(t_vm *vm);
void		put_proc(t_list *e);
#endif
