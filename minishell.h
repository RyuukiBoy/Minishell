/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/04 09:15:03 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdbool.h>

# define KRED  "\x1B[31m"
# define KWHT  "\x1B[37m"

typedef struct s_iof
{
	int		infd;
	int		outfd;
}		t_iof;

typedef struct s_cmd
{
	char	**cmd;
	int		infd;
	int		outfd;
	struct s_cmd *next;
}		t_cmd;

typedef struct	s_all
{
	t_iof	*fd;
	t_cmd	*cmd;
}		t_all;

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env *next;
}		t_env;

typedef struct s_builtin
{
	int		input;
	int		output;
	int		a;
	int		b;
	int		c;
	int		d;
	int		i;
	int		j;
	int		y;
	int		start;
	int		end;
	int		move_b;
	int		move_start;
	int		move_end;
	int		args;
	int		space;
	int		new_line;
	int		pid;
	int		p[2];
	int		exe;
	int		str_a;
	int		str_b;
	int		str_c;
	int		start_red;
	int		end_der;
	char	*pipe_cmd;
	char	**phrase;
	char	*name;
	char	**env;
	char	*new_name;
	char	*line;
	char	*first_line;
	char	*value;
	char	**split_path;
	char	**full_path;
	char	**cmd;
	char	*fcmd;
	char	**env_path;
	char	*path;
	char	*path1;
	char	*path2;
}			t_builtin;

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


int	g_exit_status;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/* function utils */

void	check_av_ac(int ac, char **av);
void	after_cmd(char *cmd, t_builtin *arr, t_iof *fd);
char	*any_cmd(char *cmd, t_builtin *arr, t_iof *fd);
void	check_qoutes(char *cmd, t_builtin *arr);
void	check_last_qoutes(char **cmd, int c, t_builtin *arr);
void	check_first_qoutes(char **cmd, int c, t_builtin *arr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_execve(char const *s1, char const *s2);
void	add_back_cmd(t_cmd **head, char **cmd, t_iof *fd);
t_cmd	*last_node_cmd(t_cmd **env);
t_cmd	*add_cmd(char **cmd, t_iof *fd);
char	**ft_strdup_double(char **s1);
void	ft_free_double(char **cmd);
int		ft_strlen_double(char *cmd, t_builtin *arr);
int		size_list_cmd(t_cmd *cmd, t_builtin *arr);

/* test_function */

void	check_cmd(char **cmd, t_builtin *arr, t_env *new_env);
char	**check_path_env(t_env *new_env, t_builtin *arr);
// void	first_cmd(t_pipe **cmd, t_builtin *arr);
// void	second_cmd(t_pipe **cmd, t_builtin *arr);
// void	last_cmd(t_pipe **cmd, t_builtin *arr);
// void	exec_multi_seco_cmd(t_pipe **cmd, t_builtin *arr);
void	execve_cmd_test(t_builtin *arr);
// void	access_multi_cmd(t_pipe **cmd, t_builtin *arr);
// void	exec_multi_cmd(t_pipe **cmd, t_builtin *arr);
// t_pipe	*create_cmd_list(char *line);
// t_pipe	*init_cmd(char *line);

/* start builtin function */

void	builtin_cd(char **av);
void	builtin_pwd(void);
int		echo_space(char **av, t_builtin *arr);
void	print_echo(char **av, int args, t_builtin *arr);
void	builtin_echo(char **av, int args, t_builtin	*arr);
t_env	*add_env(char *name, char *value);
t_env	*last_node(t_env **env);
void	add_back(t_env **head, char *name, char *value);
void	print_env(t_env *head);
t_env	*builtin_env(char **env, t_builtin *arr, t_env *head);
void	print_export(t_env *head);
t_env	*sort_export(t_env *head, t_builtin *arr);
t_env	*before_sort(t_env *head);
void	builtin_add(t_env **head, t_builtin *arr, char **add);
void	builtin_export(t_env *head, char **add, t_builtin *arr);
void	check_unset(t_builtin *arr, char **add);
void	check_cmd_unset(t_builtin *arr, char **add);
void	delete_unset(t_env **head, t_builtin *arr);
void	builtin_check(t_env **head, t_builtin *arr, char **add);
void	builtin_unset(t_env *head, t_builtin *arr, char **add);
void	check_first_char(t_builtin *arr, char **add);
void	swap_env(t_env *new_node, t_env *tmp, t_builtin *arr);
char	*ft_strdup_unset(const char *s1);
int		size_stack(t_env *head);
int		check_add(t_env **head, t_builtin *arr);
void	check_after_back(t_builtin *arr, char **add);
void	check_path(t_builtin *arr, char **add);
void	check_char(t_builtin *arr, char **add);

/* end builtin function */

/* start single cmd function */

void	check_single_cmd(t_all all, t_builtin *arr, t_env *new_env);
void	builtin_child(char *input, t_env *new_env, t_builtin *arr);
void	single_cmd(t_all all, t_builtin *arr);
void	access_single_cmd(t_all all, t_builtin *arr);
char	**put_env_array(t_env **new_env, t_builtin *arr, int space);
int		size_list(t_env **new_env, t_builtin *arr);
char	*ft_strjoin_exe(char const *s1, char const *s2);
char	**check_env_path(t_env **new_env, t_builtin *arr);
void	single_here_doc(t_builtin *arr, char **args);
void	execve_cmd(t_all all, t_builtin *arr);
void	execve_path_cmd(t_all all, t_builtin *arr);

/* end single cmd function */

/* start get_next_line function */

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strdup_get(char *str);
int		ft_strlen_get(const char *str);
char	*ft_read(char *stock, int fd);
char	*ft_line(char *str);
char	*ft_save(char *str);
char	*ft_strchr_get(char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strtrim(char const *s1, char const *set);

/* end get_next_line function */

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
char	***split_cmds(char *str);
char	**split_pipes(char *str);
int		count_args(char *str);
int		check_all_opers(int *arr);
char	*add_spaces(char *str);
int		skip_whitespaces(char *str, int i);
void	redirect(char **cmd, t_iof *file);
int		parse(char *line);
int		*get_tokens(char **cmd);

#endif