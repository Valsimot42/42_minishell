# Program
NAME	= minishell

# Compilation
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
# FSANITIZE = -fsanitize=address
# add $(FSANITIZE) to flags

# LINKER COMMANDS: Choose depending on your OS and replace accordingly
SCHOOLINC = -I $(HOME)/goinfre/.brew/opt/readline/include/
SCHOOLLIB = -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

M1INC = -I /opt/homebrew/Cellar/readline/8.2.1/include
M1LIB = -L /opt/homebrew/Cellar/readline/8.2.1/lib -lreadline

LINUXINC = -I /usr/local/opt/readline/include/
LINUXLIB = -L /usr/local/opt/readline/lib -lreadline

HEADER	= ./minishell.h	
# Sources 
SRC_PATH = src/

SRC		=	main.c						\
			initialize.c				\
			errors/error_msg.c			\
			builtins/builtins.c			\
			builtins/b_cd_00.c			\
			builtins/b_cd_01.c			\
			builtins/b_env.c			\
			builtins/b_export_00.c		\
			builtins/b_export_01.c		\
			builtins/b_export_02.c		\
			builtins/b_export_03.c		\
			builtins/b_pwd.c			\
			builtins/b_exit.c			\
			builtins/b_echo.c			\
			builtins/b_unset.c			\
			env/env_00.c				\
			env/env_01.c				\
			executor/exe_00.c			\
			executor/exe_01.c			\
			executor/exe_02.c			\
			free/free_00.c				\
			free/free_01.c				\
			lexer/lexer.c				\
			lexer/lexer_redir.c			\
			lexer/lexer_pretoken.c		\
			lexer/lexer_utils0.c		\
			lexer/lexer_utils1.c		\
			signals/signals.c			\
			signals/signal_handler.c 	\
			utils/ft_split.c			\
			utils/utils_0.c 			\
			utils/utils_1.c 			\
			utils/utils_2.c 			\
			utils/utils_3.c				\
			utils/utils_4.c				\
			utils/utils_lists.c			\
			parser/parser_00.c			\
			parser/parser_01.c			\
			parser/parser_02.c			\
			parser/parser_03.c			\
			parser/parser_04.c			\
			parser/parser_05.c			\

# REMOVE LEXER TYPE CHECKER
		
SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Colors
NC			:= \033[0m
RED			:= \033[0;31m
GREEN		:= \033[0;32m
BLUE		:= \033[0;34m

# Rules
all: $(NAME) 

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADER)
	@echo "$(GREEN)Compiling: $< $(NC)"
	@$(CC) -c $(CFLAGS) $(SCHOOLINC) -o $@ $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)builtins/
	@mkdir $(OBJ_PATH)env/	
	@mkdir $(OBJ_PATH)errors/
	@mkdir $(OBJ_PATH)free/
	@mkdir $(OBJ_PATH)lexer/
	@mkdir $(OBJ_PATH)parser/
	@mkdir $(OBJ_PATH)executor/
	@mkdir $(OBJ_PATH)signals/
	@mkdir $(OBJ_PATH)utils/

$(NAME): $(OBJ_PATH) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(SCHOOLLIB)
	@echo "$(BLUE) $(NAME) created $(NC)"

bonus: all

clean:
	@echo "Cleaning: $(RED) $(OBJ_PATH) $(NC)"
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "Cleaning:$(RED) $(NAME) $(NC)"
	@rm -f $(NAME)

re:	clean fclean all

norm:
	cd src && norminette -R CheckForbiddenSourceHeader $(SRC)
	norminette -R CheckForbiddenSourceHeader $(HEADER)

#valgrind options
# --leak-check=full --show-leak-kinds=all --ignore-fn=readline ./minishell
# --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell
valg:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes -s ./minishell

.PHONY: all, libft, clean, fclean
