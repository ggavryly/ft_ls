# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggavryly <marvin42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 11:32:42 by ggavryly          #+#    #+#              #
#    Updated: 2018/10/26 16:07:44 by ggavryly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC = -I ./include/

FLAGS = -Wall -Wextra -Werror

SRC_PATH = src/

SRCS_NAME = *.c
SRCO_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(SRC_PATH)$(SRCS_NAME) $(INC)
	@ar rc $(NAME) $(SRCO_NAME)
	@ranlib $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re