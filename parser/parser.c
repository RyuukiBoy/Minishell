/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:27:19 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/01 13:38:06 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_cmd	*parse_cmd(char *input)
{
	t_cmd	*cmd;
	char	**args;
	int		i;

	i = 0;
	args = ft_split(input, ' ');
	cmd = NULL;
	if (args[0])
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->args = (char **)malloc(sizeof(char *) * (ft_tablen(args) + 1));
		while (args[i])
		{
			cmd->args[i] = ft_strdup(args[i]);
			i++;
		}
		cmd->args[i] = NULL;
	}
	return (cmd);
}

void	add_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	if (!*head)
	{
		*head = cmd;
		(*head)->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
		tmp->next->next = NULL;
	}
}

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	path = find_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

t_cmd	*parse(char *input, char **env)
{
	t_cmd	*cmd;
	char	*path;

	cmd = parse_cmd(input);
	if (!cmd)
		return (NULL);
	path = find_cmd(cmd->args[0], get_env(env));
	if (path)
	{
		free(cmd->args[0]);
		cmd->args[0] = path;
	}
	return (cmd);
}

//void	execute(t_cmd *cmd)
//{
//	pid_t	pid;
//	int		status;

//	pid = fork();
//	if (pid == 0)
//	{
//		if (execve(cmd->args[0], cmd->args, NULL) == -1)
//			printf("error\n");
//	}
//	else
//	{
//		waitpid(pid, &status, 0);
//	}
//}

//int	main(int argc, char **argv, char **env)
//{
//	char	*input;
//	t_cmd	*cmd;
//	t_cmd	*head;

//	(void)argc;
//	(void)argv;
//	head = NULL;
//	while (1)
//	{
//		input = readline(KRED"minishell$ "KWHT);
//		if (!input)
//			break ;
//		add_history(input);
//		cmd = parse(input, env);
//		add_cmd(&head, cmd);
//		while (head)
//		{
//			execute(head);
//			head = head->next;
//		}
//	}
//}
