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

NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFTDIR = ../libft

SRCS = 	ft_printf.c ft_putchar.c ft_putstr.c ft_puthex.c ft_putnumb.c ft_putnumb_u.c ft_putpointer.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

makelibft:
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

$(NAME): makelibft $(OBJS)
	@ar -r $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)
	@cd $(LIBFTDIR) && make clean
	
fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFTDIR) && make fclean
	
re: fclean all
