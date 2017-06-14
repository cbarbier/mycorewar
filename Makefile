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
CFLAGS			= -Wall -Wextra -Werror
CORE_HDR			= includes/corewar.h
ASM_HDR				= includes/asm.h
CORE_SRCS			= core_srcs/main.c

ASM_SRCS			= asm_srcs/main.c

CORE_OBJS			= $(CORE_SRCS:.c=.o)
ASM_OBJS			= $(ASM_SRCS:.c=.o)

all: $(CORE) $(ASM) 
	@echo " / \   / \   / \   / \   / \   / \   / \ "
	@echo "( c ) ( o ) ( r ) ( e ) ( w ) ( a ) ( r )"
	@echo " \_/   \_/   \_/   \_/   \_/   \_/   \_/ "

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CORE): $(LIB) $(CORE_OBJS) $(CORE_HDR)
	@$(CC) $(CFLAGS) -o $(CORE) $(CORE_OBJS) -Llibft -lft
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
