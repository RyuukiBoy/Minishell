NAME= minishell
CFLAGS= #-fsanitize=address -g3
CC= cc
ReadLine = -lreadline  -L /Users/oait-bad/Desktop/readline-8.2 -I/Users/oait-bad/Desktop/readline-8.2 -lcurses

SRC= parser/expand.c parse_v2/check_opers.c parse_v2/split_input.c parse_v2/expanding.c parse_v2/get_tokens.c builtin/builtin_exit_multi.c \
	 libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_calloc.c libft/ft_bzero.c libft/ft_memset.c \
	 libft/ft_strjoin.c libft/ft_strnstr.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_split.c libft/ft_strchr.c libft/ft_isalnum.c \
	 libft/ft_itoa.c libft/ft_isdigit.c builtin/builtin_cd_pwd.c builtin/builtin_echo.c builtin/builtin_env.c builtin/builtin_export.c \
	 builtin/builtin_unset.c function_utils/function_utils_1.c function_utils/function_utils_2.c function_utils/function_utils_3.c \
	 builtin/builtin_utilis_2.c builtin/builtin_utilis.c get_next_line/get_next_line_utilis.c get_next_line/get_next_line.c \
	 execution/check_single_cmd.c execution/exec_single_cmd.c parse_v2/parse_files.c parse_v2/handle_quotes.c builtin/builtin_exit.c \
	 execution/single_cmd.c execution/multi_pipe.c libft/ft_putstr_fd.c libft/ft_putchar_fd.c parse_v2/parse_utils.c parse_v2/parse.c \
	 function_utils/function_utils.c function_utils/function_utils_0.c libft/ft_strtrim.c function_utils/function_utils_4.c libft/ft_atoi.c \
	 execution/here_doc.c minishell.c \

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