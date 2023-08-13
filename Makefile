# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 12:53:21 by edrouot           #+#    #+#              #
#    Updated: 2023/08/13 15:08:41 by edrouot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

SRCS = src/main/minishell.c \
		src/main/minishell_utils.c \
		src/executor/executor.c \
		src/executor/redirections.c \
		src/executor/single_command.c \
		src/executor/single_command_utils.c \
		src/executor/piped_command.c \
		src/executor/heredoc.c \
		src/executor/heredoc_utils.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_token.c \
		src/lexer/lexer_token_utils.c \
		src/lexer/lexer_init.c \
		src/lexer/lexer_expand_var.c \
		src/lexer/lexer_expand_var_utils.c \
		src/parser/parser_main.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/pwd.c \
		src/builtins/cd.c \
		src/builtins/cd_utils.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/export_utils.c \
		src/builtins/export_env.c \
		src/builtins/export_utils_ext.c \
		src/builtins/export_bis.c \
		src/builtins/unset.c \
		src/parser/parser_utils.c \
		src/parser/parser_triage.c \
		src/parser/parser_cmd_lst.c \
		src/parser/parser_redir.c \
		src/errors/errors.c \
		src/errors/errors_utils.c \
		src/signals/signals.c

OBJS = $(SRCS:.c=.o)

HEADERS = minishell.h

CFLAGS = -Wall -Wextra -Werror -g

.c.o:
				@cc ${CFLAGS} -c $^ -o $@

all:		$(NAME)

${NAME}: 	$(OBJS)
						@make -sC ./libft
						@cc $(OBJS) $(CFLAGS) -o $(NAME) -lreadline $(LIBFT)
						@echo "\033[1;5mProgram is ready!\033[0m"

clean: 
						@rm -f $(OBJS)
						@make clean -C libft

fclean: clean
						@rm -f $(NAME)
						@make -C libft fclean -s
						@echo "\033[1mAll clean!\033[0m"

re:	fclean all

.PHONY:	all clean fclean re
