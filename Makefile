NAME_PROJECT = blackjack

SRCS = $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

#valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes
FLAGS = -Wall -Wextra -Werror -Iinc/ #-fsanitize=address -g 
#hlindeza;141250.00;84;37;35;12;120000.00;-9500.00;289518.00;151018.00

all: $(NAME_PROJECT)

.PHONY: all clean fclean re

$(NAME_PROJECT): $(OBJS)
	@cc $(FLAGS) $(OBJS) $(RLFLAG) $(LIBFT) -o $(NAME_PROJECT) -lm
	@echo  "$(CYAN)Build ($(NAME_PROJECT)): $(GREEN)[Success]$(RESET)"

%.o: %.c
	@cc -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME_PROJECT) 
	@echo  "$(YELLOW)Cleaned $(CYAN)$(NAME_PROJECT): $(RED)[Success]$(RESET)"

re: fclean all

exec:
	@make re && clear && ./$(NAME_PROJECT)
rv:
	@make re && valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME_PROJECT)
v:
	@make && clear && valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME_PROJECT)
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED	= \033[1;31m
RESET = \033[0m
