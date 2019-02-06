.PHONY: all clean fclean re

NAME = ft_ls
SRC = main.c

SRO = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		make -C ./libft
		make -C ./ft_printf
		gcc $(SRC) -I ft_ls.h -o $(NAME) -L. ./libft/libft.a -L. ./ft_printf/libftprintf.a

clean:
		make clean -C ./libft
		make clean -C ./ft_printf
		rm -f $(SRO)
fclean: clean
		make fclean -C ./libft
		make fclean -C ./ft_printf
		rm -f $(NAME)
re: fclean all