# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 12:53:21 by edrouot           #+#    #+#              #
#    Updated: 2023/08/06 08:04:40 by edrouot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT = ./libft/libft.a

SRCS	= src/minishell.c \
		src/executor/executor.c \
		src/executor/single_command.c \
		src/executor/heredoc.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_token.c \
		src/lexer/lexer_init.c \
		src/lexer/lexer_expand_var.c \
		src/parser/parser_main.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/pwd.c \
		src/builtins/cd.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/parser/parser_utils.c \
		src/parser/parser_triage.c \
		src/parser/parser_cmd_lst.c \
		src/parser/parser_redir.c \
		src/errors/errors.c \
		src/signals/signals.c

OBJS	= $(SRCS:.c=.o)

CC 	= cc 

CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)

${NAME}: $(OBJS)
	@make -C ./libft
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline $(LIBFT)
	@echo "Compiling complete"

clean: 
	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re:	fclean all

.PHONY:	all clean fclean re
