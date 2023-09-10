/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:28 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/13 00:53:12 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		return ;
}

void	dup_check(t_builtin	*arr, int ac, char **av)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	check_av_ac(ac, av);
	arr->xa = dup(0);
	arr->ya = dup(1);
}

void	every_dup(t_builtin	*arr)
{
	dup2(arr->xa, 0);
	dup2(arr->ya, 1);
}

void	before_exection(t_builtin *arr, t_env *new_env, t_env *head)
{
	arr->bf_cmd = ft_split_qoutes(arr->first_line, '|');
	free(arr->first_line);
	expation(arr, new_env);
	check_cmd(arr->bf_cmd, arr, &head);
}

int	main(int ac, char **av, char **env)
{
	t_builtin	*arr;
	t_env		*head;
	t_env		*new_env;

	head = NULL;
	arr = (t_builtin *)malloc(sizeof(t_builtin));
	arr->env_v = env;
	dup_check(arr, ac, av);
	new_env = builtin_env(env, arr, &head);
	while (1)
	{
		arr->here_exit = 0;
		signal(SIGINT, SIG_IGN);
		every_dup(arr);
		arr->first_line = readline(KRED"minishell$ "KWHT);
		if (!arr->first_line)
			break ;
		add_history(arr->first_line);
		if (parse(arr->first_line))
			before_exection(arr, new_env, head);
		else
			free(arr->first_line);
	}
	printf("exit\n");
	return (g_exit_value);
}
