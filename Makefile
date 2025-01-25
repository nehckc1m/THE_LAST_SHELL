NAME = minishell
CC = cc
LIBFT = ./libft/libft.a
INCLUDES = -Iinclude
OBJECTS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -g $(INCLUDES)
LFLAGS = -L./libft -lft

SRCS =		srcs/main.c \
		srcs/signals.c \
		srcs/Parsing/split_prompt.c \
		srcs/Parsing/node_utils.c \
		srcs/Parsing/utils.c \
		srcs/Parsing/utils2.c \
		srcs/Parsing/utils3.c \
		srcs/Parsing/redirection_list.c \
		srcs/Parsing/redirection_utils.c \
		srcs/Parsing/redirection_utils2.c \
		srcs/Parsing/ft_free.c \
		srcs/Parsing/ft_expand.c \
		srcs/Parsing/check_syntax.c \
		srcs/Exec/Builtin/ft_cd.c\
		srcs/Exec/Builtin/ft_echo.c\
		srcs/Exec/Builtin/ft_export.c\
		srcs/Exec/Builtin/ft_env.c\
		srcs/Exec/Builtin/ft_unset.c\
		srcs/Exec/Builtin/ft_exit.c\
		srcs/Exec/ft_exec.c\
		srcs/Exec/utils/exec_utils.c\
		srcs/Exec/utils/exec_utils2.c\
		srcs/Exec/utils/linkedlist_utils.c\
		srcs/Exec/utils/linkedlist_utils2.c\
		srcs/Exec/utils/exec_list.c\
		srcs/Exec/here_doc.c\
		srcs/Exec/ft_free_exec.c\
		srcs/Exec/utils/debug.c\
		srcs/Exec/free_exec2.c\
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

all : $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(LFLAGS) -lreadline

$(LIBFT):
	@echo "=== Compiling libft ==="
	make -C ./libft
	@echo "=== Libft compilation done ==="


%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./libft


re: fclean all

.PHONY: all clean fclean re

