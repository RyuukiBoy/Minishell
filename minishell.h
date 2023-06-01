/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/01 13:17:54 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define KRED  "\x1B[31m"
# define KWHT  "\x1B[37m"

# define PIPE 1
# define LESSER 2
# define GREATER 3
# define LEFT_PAR 4
# define RIGHT_PAR 5
# define DOLLAR_SIGN 6
# define ASTERISK 7
# define SINGLE_QUOTE 8
# define DOUBLE_QUOTE 9
# define SPACE 10
# define HEREDOC 11
# define APPEND 12
# define WORD 13
# define INDOUBLE 14
# define INSINGLE 15
# define DEFAULT 16

typedef struct s_lexer
{
	char			*input;
	int				i;
	int				type;
	char			*value;
	struct s_lexer	*tokens;
	struct s_lexer	*current_token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}				t_lexer;

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
	char			**args;
	char			**envp;
	char			*cmd;
	char			*path;
	struct s_cmd	*next;
}				t_cmd;


int	check_tokens(t_lexer *lexer, t_lexer **token);
int	check_quotes(t_lexer *lexer, t_lexer **token);
t_lexer	*the_lexer(char *input);
char	*check_words(t_lexer *lexer, int *index);
int	node_init(t_lexer **token);
char	**get_env(char **env);
char	**dollar_sign(char **args, char **envp);
char	*get_env_value(char *key, char **env);
char	*get_env_key(char *input);
char	*delete_quotes(char *str);
char	*expand_inside_quotes(char *str);
char	**get_env(char **env);
void	handle_redirections(t_cmd *cmd);

#endif