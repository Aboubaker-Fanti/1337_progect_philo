NAME = philo

CC = CC

CFLAGS = -Wall -Wextra -Werror

SRC = 	philo.c\
		philo_uti.c\
		philo_util.c\

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all