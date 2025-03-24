# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogrativ <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 16:32:50 by ogrativ           #+#    #+#              #
#    Updated: 2024/04/15 16:32:54 by ogrativ          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard *.c)
OBJS = ${SRCS:.c=.o}
NAME = get_next_line.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS} ${OBJSB}

fclean: clean
	${RM} ${NAME} ${OBJSB}

re: fclean all

.PHONY: all clean fclean re
