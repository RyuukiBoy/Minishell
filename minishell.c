/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:28 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 15:29:18 by oait-bad         ###   ########.fr       */
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

int main(int argc, char **argv, char **env)
{
	int			x;
	int			y;
	char		**cmd;
	t_env		*new_env;
	t_env		*head;
	t_builtin	*arr;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	check_av_ac(argc, argv);
	x = dup(0);
	y = dup(1);
	cmd = malloc(sizeof(char *));
	arr = (t_builtin *)malloc(sizeof(t_builtin));
	head = NULL;
	new_env = builtin_env(env, arr, &head);
	while (1)
	{
		dup2(x, 0);
		dup2(y, 1);
		arr->first_line = readline(KRED"minishell$ "KWHT);
		if (!arr->first_line)
			break ;
		add_history(arr->first_line);
		if (parse(arr->first_line))
		{
			cmd = ft_split((arr->first_line), '|');
			expand(cmd, new_env);
			check_cmd(cmd, arr, &head);
		}
		free(arr->first_line);
	}
	printf("exit\n");
	exit(0);
}
