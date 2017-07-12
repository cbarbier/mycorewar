# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/04 14:32:18 by cbarbier          #+#    #+#              #
#    Updated: 2017/05/12 18:37:35 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE			= corewar
ASM			= asm
LIB				= libft/libft.a
CC				= gcc
CFLAGS				= -Wall -Wextra -Werror
NCURSES				= -lncurses
CORE_HDR			= includes/corewar.h
ASM_HDR				= includes/asm.h
CORE_SRCS			= core_srcs/main.c \
				  core_srcs/op.c \
				  core_srcs/parse_argv.c \
				  core_srcs/parse_player.c \
				  core_srcs/parse_pcb_n_param.c \
				  core_srcs/init_vm.c \
				  core_srcs/vm_core.c \
				  core_srcs/tools.c \
				  core_srcs/debug.c \
				  core_srcs/ops/f_live.c \
				  core_srcs/ops/f_ld.c \
				  core_srcs/ops/f_add.c \
				  core_srcs/ops/f_sub.c \
				  core_srcs/ops/f_and.c \
				  core_srcs/ops/f_st.c \
				  core_srcs/ops/f_or.c \
				  core_srcs/ops/f_xor.c \
				  core_srcs/ops/f_sti.c \
				  core_srcs/ops/f_ldi.c \
				  core_srcs/ops/f_zjmp.c \
				  core_srcs/ops/f_fork.c \
				  core_srcs/ops/f_lld.c \
				  core_srcs/ops/f_lldi.c \
				  core_srcs/ops/f_lfork.c \
				  core_srcs/ops/f_aff.c

ASM_SRCS			= asm_srcs/main.c

CORE_OBJS			= $(CORE_SRCS:.c=.o)
ASM_OBJS			= $(ASM_SRCS:.c=.o)

all: $(CORE) $(ASM) 
	@echo " / \   / \   / \   / \   / \   / \   / \ "
	@echo "( c ) ( o ) ( r ) ( e ) ( w ) ( a ) ( r )"
	@echo " \_/   \_/   \_/   \_/   \_/   \_/   \_/ "

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -Iincludes

$(CORE): $(LIB) $(CORE_OBJS) $(CORE_HDR)
	@$(CC) $(CFLAGS) $(NCURSES) -o $(CORE) $(CORE_OBJS) -Llibft -lft 
	@echo "COREWAR BUILT\t\t\033[0;32m✓\033[0m"

$(ASM): $(LIB) $(ASM_OBJS) $(ASM_HDR)
	@$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJS) -Llibft -lft
	@echo "ASM BUILT\t\t\033[0;32m✓\033[0m"
$(LIB):
	@make -C libft

clean:
	@/bin/rm -rf $(CORE_OBJS)
	@/bin/rm -rf $(ASM_OBJS)
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(CORE)
	@/bin/rm -rf $(ASM)
	@make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
