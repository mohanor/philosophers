NAME = philo

src = utils/utils.c utils/utils_2.c utils/atoi.c philosophers.c


obj = $(src:.c=.o)


flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):  $(obj) philosophers.h
	cc $(flags) $(obj) -o $(NAME)

%.o: %.c philosophers.h
	cc -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean all