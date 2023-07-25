/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/25 13:37:17 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define KRED  "\x1B[31m"
# define KWHT  "\x1B[37m"

typedef enum e_type
{
	CMD_NAME = 1,
	ARG,
	R_IN_SIG,
	R_OUT_SIG,
	R_IN_FILE,
	R_OUT_FILE,
	PIPE,
	R_APP_SIG,
	R_APP_FILE,
	HEREDOC_SIG,
	HEREDOC_LIM,
}			t_type;

typedef struct s_exp
{
	char			*before;
	char			*after;
	char			*key;
	char			*value;
	int				start;
	int				end;
	char			*tmp;
	char			*all_cmd;
}			t_exp;

typedef struct s_env
{
	int				i;
	char			*input;
	char			**envp;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	char			*input;
	int				i;
	int				type;
	char			*cmd;
	char			**args;
	char			**pipes;
	char			**redirections;
	char			*value;
	struct s_cmd	*next;
}				t_cmd;

int g_exit_status;

//int	check_tokens(t_lexer *lexer, t_lexer **token);
//int	check_quotes(t_lexer *lexer, t_lexer **token);
//t_lexer	*the_lexer(char *input);
//char	*check_words(t_lexer *lexer, int *index);
//int	node_init(t_lexer **token);
//char	**get_env(char **env);
//char	**dollar_sign(char **args, char **envp);
//char	*get_env_value(char *key, char **env);
//char	*get_env_key(char *input);
//int	is_special_char(char *str);
char	*delete_quotes(char *str);
//char	*expand_inside_quotes(char *str);
//char	**get_env(char **env);
//int		is_between_quotes(char *str);
//char	**split_by_pipes(char **input);

char	**split_args(char *str);
int	count_args(char *str);
int	check_all_opers(int *arr);
char	*add_spaces(char *str);
char	**split_pipes(char *str);
int		skip_whitespaces(char *str, int i);
int		check_op(char *arr);

#endif