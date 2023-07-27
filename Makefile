NAME= minishell
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3
CC= cc
ReadLine = -lreadline  -L /Users/oait-bad/Desktop/readline-8.2 -I/Users/oait-bad/Desktop/readline-8.2 -lcurses

#SRC= minishell.c lexer/lexer.c lexer/check_tokens.c parser/expand.c parser/parser.c parser/parser_utils.c parser/handle_quotes.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strncmp.c \
	 libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_split.c libft/ft_strchr.c libft/ft_strnstr.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putchar_fd.c \
	 libft/ft_strtrim.c libft/ft_lstadd_back.c libft/ft_lstnew.c 
SRC= parse_v2/handle_quotes.c parse_v2/parse.c parse_v2/parse_utils.c parse_v2/parse_files.c parse_v2/check_opers.c parse_v2/split_input.c parse_v2/expanding.c parse_v2/get_tokens.c libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_calloc.c libft/ft_bzero.c libft/ft_memset.c \
	 libft/ft_strjoin.c libft/ft_strnstr.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_split.c libft/ft_strchr.c libft/ft_isalnum.c libft/ft_itoa.c libft/ft_isdigit.c libft/ft_lstadd_back.c libft/ft_lstnew.c libft/ft_strncmp.c
OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(ReadLine) $(OBJ) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f libft.a
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re