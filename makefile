# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 12:53:21 by edrouot           #+#    #+#              #
#    Updated: 2023/07/21 15:27:37 by emiliedrouo      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

#LIBFT = ./libft/libft.a

SRCS	= src/minishell.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_token.c \
		src/lexer/lexer_envp.c \
		src/lexer/lexer_envp2.c \
		src/parser/parser1.c \
		src/parser/parser_single_command.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/pwd.c \
		utils_libft.c
			
OBJS	= $(SRCS:.c=.o)

CC 	= cc

CFLAGS = -g -Wall -Wextra -Werror 

all:	$(NAME)

${NAME}: $(OBJS)
	@make -C ./libft
	@$(CC) $(OBJS)  $(CFLAGS) -o $(NAME) -lreadline 
#$(LIBFT)
	@echo "Compiling complete"

clean: 
	@rm -f $(OBJS)
#@make clean -C libft

fclean: clean
	@rm -f $(NAME)
#@rm -f $(LIBFT)

re:	fclean

.PHONY:	all clean fclean re
