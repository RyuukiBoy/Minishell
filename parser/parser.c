/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:03:30 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/08 11:45:45 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	skip_whitespaces(char *str)
{
	if (*str == 32 && (*str >= 9 && *str <= 13))
		str++;
}

t_cmd	*create_cmd_list(char *line)
{
	t_cmd	*cmd;
	t_cmd	*head;
	char	**pipes;
	int		i;

	i = 0;
	pipes = split_by_pipes(&line);
	skip_whitespaces(line);
	cmd = init_cmd(pipes[i]);
	head = cmd;
	while (pipes[++i])
	{
		cmd->next = init_cmd(pipes[i]);
		cmd = cmd->next;
	}
	return (head);
}



// main function to test this file in a loop using readline

int main()
{
	char *line;
	t_cmd *cmd;
	while (1)
	{
		line = readline("minishell$ ");
		cmd = create_cmd_list(line);
		while (cmd)
		{
			printf("cmd->input = %s\n", cmd->input);
			cmd = cmd->next;
		}
	}
	return (0);
}