NAME= minishell
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3
CC= gcc
ReadLine = -lreadline  -L /Users/oait-bad/Desktop/readline-8.2 -I/Users/oait-bad/Desktop/readline-8.2 -lcurses

SRC= minishell.c lexer/lexer.c lexer/check_tokens.c parser/expand.c parser/handle_quotes.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strncmp.c \
	 libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_split.c libft/ft_strchr.c libft/ft_strnstr.c 
OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(ReadLine) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re