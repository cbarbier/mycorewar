NAME			= asm

COMPILER		= gcc

CC_FLAGS		= -Wall -Werror -Wextra -g

INC				= ./includes/asm.h \
				  ./includes/op.h

SRC_DIR			= ./srcs

SRC				=	main.c \
					ft_asm.c \
				    ft_tools.c \
				    ft_tools2.c \
					ft_head.c \
					ft_check.c \
				    ft_write.c \
				    ft_instr.c \
				    ft_errors.c \
					ft_header.c \
					op.c \
					ft_launcher.c

OBJ				= $(SRC:.c=.o)

SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))

NEWLINE			= @echo ""

all : $(NAME)

$(NAME): $(OBJ) $(INC)
		@$(NEWLINE)
		@echo "Compilation de la libft..."
		@$(NEWLINE)
		@echo "Compilation de l'asm..."
		@$(COMPILER) $(CC_FLAGS) $(OBJ) ./Libft/libft.a -o $(NAME)
		@$(NEWLINE)
		@echo "asm cree !"
		$(NEWLINE)

%.o: $(SRC_DIR)/%.c
		@$(COMPILER) $(CC_FLAGS) -I includes -c $< -o $@

clean:
		@echo "Suppression des objets"
		$(NEWLINE)
		@rm -rf $(OBJ)

fclean: clean
		@echo "Suppression de l'executable"
		$(NEWLINE)
		@rm -rf $(NAME)

re: fclean 
		@$(MAKE) all

.PHONY: all clean fclean re
