NAME = so_long
# CHECK = checker

SRCS = test.c\

OBJS = $(SRCS:.c=.o)

CC = libmlx42.a -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

# $(CHECK): $(CHECK_OBJS)
# 		$(CC) $(CHECK_OBJS) libft/libft.a -o $(CHECK)

clean:
		rm -f $(OBJS)
#rm -f $(CHECK_OBJS)

fclean: clean
		rm -f $(NAME)
#rm -f $(CHECK)

re: fclean all

.PHONY: all clean fclean re
