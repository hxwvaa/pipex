NAME = pipex

SRCS = 	pipex.c\
		utils.c\
		libft/libft.a\

SRCS_BONUS = pipex_bonus.c\
			utils_bonus.c\
			libft/libft.a\

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

$(NAME) :
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

bonus : clean
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME)