/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:03:30 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/11 01:26:36 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

//t_cmd	*init_cmd(char *line)
//{
//	t_cmd	*cmd;

//	cmd = (t_cmd *)malloc(sizeof(t_cmd));
//	cmd->input = ft_strdup(line);
//	cmd->args = NULL;
//	cmd->pipes = NULL;
//	cmd->redirections = NULL;
//	cmd->next = NULL;
//	return (cmd);
//}

//void	split_by_spaces(t_cmd *cmd)
//{
//	char	**args;
//	int		i;

//	i = 0;
//	args = ft_split(cmd->input, ' ');
//	cmd->args = args;
//}

//t_cmd	*create_cmd_list(char *line)
//{
//	t_cmd	*cmd;
//	t_cmd	*head;
//	char	**pipes;
//	int		i;

//	i = 0;
//	pipes = split_by_pipes(&line);
//	cmd = init_cmd(pipes[i]);
//	split_by_spaces(cmd);
//	head = cmd;
//	while (pipes[++i])
//	{
//		cmd->next = init_cmd(pipes[i]);
//		cmd = cmd->next;
//	}
//	return (head);
//}

//int main()
//{
//	char *line;
//	t_cmd *cmd;

//	while (1)
//	{
//		line = readline ("minishell$ ");
//		if (!line)
//		   break ;
//		add_history(line);
//		cmd = create_cmd_list(line);
//		while (cmd)
//		{
//			printf("cmd : %s\n", cmd->input);
//			cmd = cmd->next;
//		}
//	}
//}
