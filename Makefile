NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c \
		pipex_command_utils.c \
		pipex_process_utils.c 
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINT_F_DIR = ./printf
PRINT_F = $(PRINT_F_DIR)/libftprintf.a
INCLUDES = -I./ -I$(LIBFT_DIR) -I$(PRINT_F_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINT_F)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINT_F) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) 

$(PRINT_F):
	make -C $(PRINT_F_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINT_F_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINT_F_DIR) fclean

re: fclean all

.PHONY: all clean fclean re