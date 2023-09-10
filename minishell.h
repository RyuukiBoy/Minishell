/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/12 22:07:00 by ybargach         ###   ########.fr       */
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
	char	**n_cmd;
	int		infd;
	int		outfd;
}		t_iof;

typedef struct s_cmd
{
	char			**cmd;
	int				infd;
	int				outfd;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_all
{
	t_iof	*fd;
	t_cmd	*cmd;
}		t_all;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_norm
{
	int		i;
	int		j;
	int		flag;
	char	*new;
}			t_norm;

typedef struct s_builtin
{
	int		arr_fd;
	int		aa;
	int		bb;
	int		here_exit;
	int		here_fd[OPEN_MAX];
	int		input;
	int		output;
	int		a;
	int		b;
	int		c;
	int		d;
	int		i;
	int		j;
	int		y;
	int		x;
	int		xa;
	int		ya;
	int		*exitstatus;
	int		*exitarray;
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
	int		her_p[2];
	int		her_f;
	int		exe;
	int		str_a;
	int		str_b;
	int		str_c;
	int		start_red;
	int		end_der;
	int		*add_b;
	int		add_a;
	int		add_c;
	int		exit;
	int		*ex_a;
	int		ex_b;
	char	*del_quot;
	char	*pipe_cmd;
	char	**phrase;
	char	*name;
	char	**env;
	char	*new_name;
	char	*new_value;
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
	char	*no;
	char	**env_v;
	char	**bf_cmd;
	char	*cmd_ns;
	char	**a_cmd;
	int		aloc_a;
	int		arr_a;
	int		arr_b;
	int		old_lin;
	int		quot_en;
	int		quot_st;
	int		expa_s;
	int		expa_e;
	int		expa_af;
	int		expa_b;
	int		expa_a;
	int		expa_m;
	int		quot_s;
	int		quot_e;
	int		quot_b;
	int		quot_a;
	int		quot_n;
	char	*char_bef;
	char	*char_aft;
	char	*char_now;
	char	*quo_bef;
	char	*quo_aft;
	char	*quo_after;
	char	*quo_befor;
	char	*quo_now;
	char	*joi_quo;
	char	*quo_half;
	char	*quo_out;
	char	*quo_new;
	char	*quo_lin;
	char	*now_equa;
	char	*now_new;
	char	*half_line;
	char	*sin_bef;
	char	*sin_aft;
	char	*sin_now;
	char	*sin_line;
	int		sin_a;
	int		sin_be;
	int		sin_n;
	int		sin_s;
	int		sin_e;
}			t_builtin;

typedef struct s_quote
{
	int		i;
	int		o_len;
	int		i_len;
	char	c;
}			t_quote;

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

int	g_exit_value;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

void	close_all_fd(t_builtin *arr);
void	exit_all_fd(t_builtin *arr, t_all all, char **b_cmd, char **n_cmd);
void	check_cmd_norm(t_builtin *arr, t_env **new_env, t_all all);
void	redirect(char **cmd, t_builtin *arr, t_all all);
void	redir_for_norm(char **cmd, t_builtin *arr, t_all all, char *b_limir);
void	here_norm(t_all all, t_builtin *arr, char *b_limir);
int		check_name_file(char *cmd);
int		check_opera_file(char *cmd, int a);
void	file_err(char *file);
void	quo_number(t_builtin *arr, int a);
void	expaton_norm(t_builtin *arr, t_env *new_env);
int		check_expa(t_builtin *arr);
int		ft_strlen_int(const char *str);
void	expation(t_builtin *arr, t_env *new_env);
void	dollar_function(t_builtin *arr, t_env *new_env);
void	more_norm(t_all all, char *b_limir);
char	*space_limt(char *cmd);
void	file_error(char *cmd);
// builtin_cd_pwd

void	builtin_pwd(t_builtin *arr);
void	builtin_cd(char **av, t_env *env, t_builtin *arr);
void	change_in_env(char *old_pwd, t_env *env);

// builtin_echo

void	builtin_echo(char **av, t_builtin *arr);
int		echo_space(char **av, t_builtin *arr);

// builtin_env

t_env	*builtin_env(char **env, t_builtin *arr, t_env **head);
void	print_env(t_env *head, t_builtin *arr);
t_env	*env_null(t_builtin *arr, t_env **head);
void	add_back(t_env **head, char *name, char *value);
t_env	*add_env(char *name, char *value);

// builtin_exit

void	builtin_exit(char **add, t_builtin *arr);
void	check_exit(char **add, t_builtin *arr);
void	many_error_exit(void);
void	welcome_to_exit(char *add, t_builtin *arr);
int		ft_strlen_pointer(char **add);

// builtin_exit_multi

void	builtin_exit_multi(char **add, t_builtin *arr);
void	check_exit_multi(char **add, t_builtin *arr);
void	many_error_exit_multi(void);
void	welcome_to_exit_multi(char *add, t_builtin *arr);
void	print_error_exit_multi(char *add);

// builtin_export

void	builtin_export(t_env *head, char **add, t_builtin *arr);
void	builtin_add(t_env **head, t_builtin *arr, char *add);
t_env	*sort_export(t_env *head, t_builtin *arr);
void	print_export(t_env *head);

// builtin_unset

void	builtin_unset(t_env **head, t_builtin *arr, char **add);
void	builtin_check(t_env **head, t_builtin *arr, char **add);
void	delete_unset(t_env **head, t_builtin *arr);
void	check_cmd_unset(t_builtin *arr, char **add);
void	check_unset(t_builtin *arr, char **add);

// builtin_utilis_2

int		check_add_equal(t_env **head, t_builtin *arr);
void	change_node(t_env **head, char *name, char *value);
void	export_equal(t_builtin *arr, char *add, t_env **head);
void	swap_env(t_env *new_node, t_env *tmp, t_builtin *arr);
int		check_first_char(char*add);

// builtin_utilis_3

char	*ft_substr_equal(char const *s, unsigned int start, size_t len);
char	*ft_join_utils(char const *s1, char const *s2);
char	*ft_strjoin_equal(char const *s1, char const *s2);
int		check_char_nor(t_builtin *arr, char **add);
int		check_char(t_builtin *arr, char **add, t_env **new_node);

// builtin_utilis_4

void	print_error_exit(char *add);
void	print_exit(char *add);
void	print_exit_multi(char *add);
void	cmp_delete_two(t_env *current, t_env *prev);
void	cmp_delete(t_env **head, t_env *tmp, t_env *current);

// builtin_utilis 

t_env	*last_node(t_env **env);
char	*ft_strdup_unset(const char *s1);
int		size_stack(t_env *head);
void	check_add(t_env **head, t_builtin *arr);
int		*check_path(t_builtin *arr, char **add, t_env **new_node);

// check_single_cmd

char	**put_env_array(t_env **new_env, t_builtin *arr, int space);
int		size_list(t_env *new_env, t_builtin *arr);
char	*ft_strjoin_exe(char const *s1, char const *s2);
char	**check_env_path(t_env **new_env, t_builtin *arr);
int		size_list_cmd(t_cmd *cmd, t_builtin *arr);

// exec_single_cmd

void	execve_path_cmd(t_all all, t_builtin *arr);
void	execve_cmd(t_all all, t_builtin *arr);
void	access_single_cmd(t_all all, t_builtin *arr);
void	execv_single_path(t_all all, t_builtin *arr);

// here_doc

char	*ft_strjoin_here(char const *s1, char const *s2);
void	here_doc_child(t_builtin *arr, char *args);
int		here_doc_parent(t_builtin *arr);
int		here_doc(t_builtin *arr, char *args);

// multi_pipe_utils_1

void	access_function(t_all all, t_builtin *arr);
char	**check_path_env(t_env *new_env, t_builtin *arr);
void	welcome_to_multi_seco(t_all all, t_builtin *arr);
void	welcome_to_multi_first(t_all all, t_builtin *arr, t_env **new_env);
void	welcome_to_multi(t_all all, t_builtin *arr, t_env **new_env);

// multi_pipe_utils_2

void	execv_path(t_all all, t_builtin *arr);
void	execv_cmd(t_all all, t_builtin *arr);
void	free_iof(t_iof *iof);
void	free_cmd(t_cmd *head);
void	in_quote(t_builtin *arr);

// multi_pipe_utils

void	check_first_null(t_all all, t_builtin *arr);
void	check_last_cmd(t_all all, t_builtin *arr, t_env **new_env);
void	check_first_cmd(t_all all, t_builtin *arr, t_env **new_env);
void	check_second_cmd(t_all all, t_builtin *arr, t_env **new_env);
void	before_multi_cmd(t_all all, t_builtin *arr, t_env **new_env);

// multi_pipe 

void	access_path(t_all all, t_builtin *arr);
void	parent_cmd(t_all all, t_builtin *arr);
int		welcome_to_multi_v2(t_all all, t_builtin *arr, t_env **new_env);
void	multi_cmd(t_all all, t_builtin *arr, t_env **new_env);
void	check_cmd(char **b_cmd, t_builtin *arr, t_env **new_env);

// single_cmd

void	single_cmd(t_all all, t_builtin *arr);
void	welcome_to_single_excute(t_all all, t_builtin *arr);
void	check_single_cmd(t_all all, t_builtin *arr, t_env **new_env);
void	check_io_file_single(t_all all, t_builtin *arr, t_env **new_env);

// function_utils_0

char	**send_red(char	*str, t_builtin *arr);
char	*cpy_cmd(char *cmd, t_builtin *arr);
char	*dlt_cmd(char *cmd, t_builtin *arr);
char	*any_cmd(char *cmd, t_builtin *arr, t_all all);

// function_utils_1

char	**ft_split_space(char const *s, char c);

// function_utils_2

void	ft_free_double(char **cmd);
char	**ft_strdup_double(char **s1);
t_cmd	*add_cmd(char **cmd, t_iof *fd);
t_cmd	*last_node_cmd(t_cmd **env);
void	add_back_cmd(t_cmd **head, char **cmd, t_iof *fd);

// function_utils_3

void	check_av_ac(int ac, char **av);
int		ft_strlen_double(char *cmd, t_builtin *arr);
int		skip_double_quotes(char const *str, int a);
int		skip_single_quotes(char const *str, int a);
char	*ft_strjoin_execve(char const *s1, char const *s2);

// function_utils_4

char	**ft_split_qoutes(char const *s, char c);
void	check_is_expa(t_builtin *arr, t_env *new_env);
void	src_env(t_builtin *arr, t_env *new_env);
// function_utils_5

int		skip_double_space(char const *str, int a);
int		skip_single_space(char const *str, int a);
int		check_qoutes(char *cmd, t_builtin *arr);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);

// function_utils_6

char	*last_send_red(char *str, t_builtin *arr);
int		check_opera_red(char *cmd, t_builtin *arr);
int		check_opera(char *cmd, t_builtin *arr);
int		check_opera_quotes(char *cmd, t_builtin *arr);
int		check_opera_string(char *cmd, t_builtin *arr);

// function_utils_7

int		check_last_qoutes_file(char *cmd, int a);
int		check_qoutes_file(char *cmd, int a);
int		check_first_qoutes_file(char *cmd, int a);
char	*alloc_str(char *str, int start, int end);
void	exit_values(t_builtin *arr);
void	single_function(t_builtin *arr);
void	double_function_norm(t_builtin *arr, t_env *new_env);
void	dollar_function(t_builtin *arr, t_env *new_env);
void	src_env_quo(t_builtin *arr, t_env *new_env);
void	ft_free_qoutes(t_builtin *arr);
void	ft_free_dollar(t_builtin *arr);
void	src_env_quo(t_builtin *arr, t_env *new_env);

// function_utils_8

char	*sub(char const *s, unsigned int start, size_t len);
void	after_cmd_space(char *cmd, t_builtin *arr);
void	after_cmd_quotes(char *cmd, t_builtin *arr);
void	after_cmd_chara(char *cmd, t_builtin *arr);
void	after_cmd(char *cmd, t_builtin *arr, t_all all);

// function_utils

int		check_first_qoutes(char *cmd, t_builtin *arr);
int		check_last_qoutes(char *cmd, t_builtin *arr);
int		check_first_qoutes_red(char *cmd, t_builtin *arr);
int		check_last_qoutes_red(char *cmd, t_builtin *arr);
int		check_qoutes_red(char *cmd, t_builtin *arr);

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

void	rl_replace_line(const char *text, int clear_undo);
char	*delete_quotes(char *str);
char	**split_args(char *str);
char	***split_cmds(char *str);
char	**split_pipes(char *str);
int		count_args(char *str);
char	*add_spaces(char *str);
void	redirect(char **cmd, t_builtin *arr, t_all all);
int		parse(char *line);
int		*get_tokens(char **cmd);
void	expand(char **args, t_env *envp);
char	*ft_strjoin_simple(char *s1, char *s2);
void	print_it(char c);
int		check_pipes(char *line);
int		check_last_pipe(char *line);
int		norm_redirections_check(char *str);
int		check_quotes(char *str);
void	free_exp(t_exp *exp);
int		is_inside_squotes(char *str, int i);
char	*ft_substr_simple(char const *s, unsigned int start, size_t len);

#endif