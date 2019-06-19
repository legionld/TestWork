NAME1 = n_1.exe
NAME2 = n_2.exe
NAME4 = n_4.exe

all: $(NAME1) $(NAME2) $(NAME4)

$(NAME1):
	gcc n_1.c get_next_line.c -L./libft -lft -o $(NAME1)
$(NAME2):
	gcc n_2.c get_next_line.c -L./libft -lft -o $(NAME2)
$(NAME4):
	gcc n_4.c get_next_line.c -L./libft -lft -o $(NAME4)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME1) $(NAME2) $(NAME4);
re: fclean all