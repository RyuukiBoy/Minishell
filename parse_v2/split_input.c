/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:18:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/26 10:15:14 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

char	**split_args(char *str)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (count_args(str) + 1));
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			k = i;
			while (str[i] && str[i] != ' ')
				i++;
			args[j++] = ft_substr(str, k, i - k);
		}
	}
	args[j] = NULL;
	return (args);
}

int	count_pipes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**split_pipes(char *str)
{
	char	**pipes;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	pipes = (char **)malloc(sizeof(char *) * (count_pipes(str) + 2));
	while (str[i])
	{
		k = i;
		while (str[i] && str[i] != '|')
			i++;
		pipes[j++] = ft_substr(str, k, i - k);
		if (str[i])
			i++;
	}
	pipes[j] = NULL;
	return (pipes);
}

char	***split_cmds(char *str)
{
	char	***cmds;
	char	**pipes;
	int		i;
	int		j;
	int		pipe_counter;

	pipe_counter = count_pipes(str);
	cmds = (char ***)malloc(sizeof(char **) * (pipe_counter + 2));
	if (cmds == NULL)
		return (NULL);
	i = 0;
	j = 0;
	pipes = split_pipes(str);
	while (pipes[i])
	{
		cmds[j++] = split_args(pipes[i]);
		i++;
	}
	cmds[j] = NULL;
	while (i < pipe_counter + 1)
		free(pipes[i++]);
	free(pipes);
	return (cmds);
}
