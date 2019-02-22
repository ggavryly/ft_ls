.PHONY: all, clean, fclean, re.
NAME = ft_ls

LIBFT_PATH = libft/
LIBFTPRI_PATH = ft_printf/

INC = -I ./include/ -I ./$(LIBFT_PATH)include/ -I ./$(LIBFTPRI_PATH)/include/

SRCS_NAME = src/main.c \
			src/display.c \
			src/errors.c \
			src/init_info.c \
			src/list_job.c\
			src/parse_flags.c \
			src/path_manage.c \
			src/sort_list.c \
			src/flag_help.c \
			src/flag_l.c \
			src/help.c \
			src/recusive.c

SRCO_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@make -C $(LIBFTPRI_PATH)
	@gcc $(SRCS_NAME) $(INC) -L $(LIBFT_PATH) -lft -L $(LIBFTPRI_PATH) -lftprintf -o $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@make -C $(LIBFTPRI_PATH)/ clean
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@make -C $(LIBFTPRI_PATH)/ fclean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all
