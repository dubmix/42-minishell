# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdelanno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 11:56:35 by pdelanno          #+#    #+#              #
#    Updated: 2023/06/08 11:59:16 by pdelanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 

OBJS = ${SRCS:.c=.o}

HEADERS = minishell.h

CFLAGS = -g -Werror -Wall -Wextra

.c.o:
				@cc ${CFLAGS} -c $^ -o $@

all:			${NAME}

$(NAME):		${OBJS}
						@cc ${OBJS} $(CFLAGS) -o $(NAME)
						@echo "Program is ready!"

clean:
				@rm -f ${OBJS}

fclean:			clean
						@cd P.A. && rm -f ${NAME}
						@rm -f ${NAME}
						@echo "All clean!"

re: fclean all

.PHONY: all clean fclean re
