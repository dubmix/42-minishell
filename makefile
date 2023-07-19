# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 12:53:21 by edrouot           #+#    #+#              #
#    Updated: 2023/07/19 10:49:51 by edrouot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell

LIBFT = ./libft/libft.a

SRCS	= minishell.c \
		lexer_utils.c \
		lexer_token.c \
		lexer_envp.c \
		lexer_envp2.c \
		parser1.c \
		parser_single_command.c \
		src/builtins/echo.c
			
OBJS	= $(SRCS:.c=.o)

CC 	= cc

CFLAGS = -g -Wall -Wextra -Werror 

all:	$(NAME)

${NAME}: $(OBJS)
	@make -C ./libft
	@$(CC) $(OBJS)  $(CFLAGS) -o $(NAME) -lreadline $(LIBFT)
	@echo "Compiling complete"

clean: 
	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re:	fclean

.PHONY:	all clean fclean re
