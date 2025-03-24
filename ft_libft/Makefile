# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogrativ <ogrativ@student.42london.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:08:59 by ogrativ           #+#    #+#              #
#    Updated: 2024/05/20 10:09:03 by ogrativ          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_ft.a
PRINTFNAME = libftprintf.a
GNLNAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
PRINTFDIR = ./src/ft_printf
GNLDIR = ./src/get_next_line

all: $(NAME)

$(NAME): makeprintf makegnl
	@ar -x $(PRINTFDIR)/$(PRINTFNAME)
	@ar -x $(GNLDIR)/$(GNLNAME)
	@ar -rcs $(NAME) *.o
	@rm -f *.o

makeprintf:
	@make -C $(PRINTFDIR)

makegnl:
	@make -C $(GNLDIR)

clean:
	@cd $(PRINTFDIR) && make clean
	@cd $(GNLDIR) && make clean
	@rm -f *.o
	
fclean: clean
	@rm -f $(NAME)
	@cd $(PRINTFDIR) && make fclean
	@cd $(GNLDIR) && make fclean
	
re: fclean all

.PHONY: all makeprintf makegnl clean fclean re
