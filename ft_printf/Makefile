NAME = libftprintf.a

INC = -I ./include/

SRCS_NAME = *.c
SRCO_NAME = $(SRCS_NAME:.c=.o)

SRCS_PATH = src/

all: $(NAME)

$(NAME):
	@gcc -c $(SRCS_PATH)$(SRCS_NAME) $(INC)
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
