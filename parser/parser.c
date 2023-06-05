/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:27:19 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/05 22:43:50 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_between_quotes(char *str)
{
	int		single;
	int		doubleq;
	int		i;

	i = ft_strlen(str) - 1;
	single = 0;
	doubleq = 0;
	while (i >= 0)
	{
		if (str[i] == '\'')
			single++;
		if (str[i] == '\"')
			doubleq++;
		i--;
	}
	if (single % 2 == 0 && doubleq % 2 == 0)
		return (0);
	return (1);
}

char	**split_by_pipes(char **input)
{
	char	**pipes;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	pipes = (char **)malloc(sizeof(char *) * (ft_strlen(*input) + 1));
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
		{
			i++;
			while ((*input)[i] && (*input)[i] != '\'' && (*input)[i] != '\"')
				i++;
		}
		if ((*input)[i] == '|')
		{
			pipes[j] = ft_substr(*input, k, i - k);
			k = i + 1;
			j++;
		}
		i++;
	}
	pipes[j] = ft_substr(*input, k, i - k);
	pipes[j + 1] = NULL;
	return (pipes);
}

t_cmd	*init_cmd(char *line)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->input = ft_strdup(line);
	cmd->args = NULL;
	cmd->pipes = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*create_cmd_list(char *line)
{
	t_cmd	*cmd;
	t_cmd	*head;
	char	**pipes;
	int		i;

	i = 0;
	pipes = split_by_pipes(&line);
	cmd = init_cmd(pipes[i]);
	head = cmd;
	while (pipes[++i])
	{
		cmd->next = init_cmd(pipes[i]);
		cmd = cmd->next;
	}
	return (head);
}
