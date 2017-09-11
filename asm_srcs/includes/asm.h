/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      asm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 13:29:11 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/08 13:45:44 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "../Libft/printf/printf.h"
# include "../Libft/srclib/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <stdio.h>

typedef struct  s_champ
{
	int           instr;
	int           lab;
	int           err;
	char          *line;
	char          *label;
	char          *op;
	int            opcode;
	unsigned char codage;
	char          *args;
	char          **arg;
	unsigned char *param;
	int           size;
	struct s_champ *next; 
	int            errcode;
	int            ligne;
	int            col;
}               t_champ;

typedef struct		s_asm
{
	int     fd;
	char    *origin;
	char    *file;
	char    *name;
	char    *comment;
	char    header[16 + PROG_NAME_LENGTH + COMMENT_LENGTH];
	t_champ *champ;
}			            t_asm;

typedef struct		s_op
{
	char		*param;
	int			nbargs;
	int			*arg;
	int			opcode;
	int			cycle;
	char		*name;
	int			ocod;
	int			oind;
}                 t_op;

int				ft_launcher(char *file);
int				ft_head(t_asm *sfile);
int				ft_set_header(t_asm *sfile);
int				ft_asm(t_asm *sfile, t_champ *champ);
void			ft_write(t_asm *sfile, t_champ *champ);
int				ft_instr(t_champ *champ);
int				ft_check(char *op, char *param, t_champ *champ);
int				ft_split_param(char c);
int				ft_nb_split(char *str, int i);
int				ft_find_op(char *op);
char			*ft_erspace(char *str);
void			ft_error(t_asm *sfile);

#endif
