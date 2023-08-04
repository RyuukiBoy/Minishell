/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:28 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/04 09:13:22 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**cmd;
	t_env	*new_env;
	t_env	*head;
	t_builtin	*arr;

	check_av_ac(argc, argv);
	cmd = malloc(sizeof(char *));
	arr = (t_builtin *)malloc(sizeof(t_builtin));
	head = NULL;
	new_env = builtin_env(env, arr, head);
	while (1)
	{
		line = readline(KRED"minishell$ "KWHT);
		if (!line)
			break ;
		add_history(line);
		if (parse(line))
		{
			arr->d = 0;
			cmd = ft_split(add_spaces(line), '|');
			check_cmd(cmd, arr, new_env);
			arr->d++;
		}
		free(line);
	}
}
