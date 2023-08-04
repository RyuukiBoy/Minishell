/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:40:45 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 14:19:13 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_double(char **cmd)
{
	int	a;

	if (cmd == NULL)
		return ;
	a = 0;
	while (cmd[a])
	{
		free(cmd[a]);
		cmd[a] = NULL;
		a++;
	}
	free(cmd);
}

char	**ft_strdup_double(char **s1)
{
	char	**s2;
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (s1[a])
		a++;
	s2 = malloc((a + 1) * sizeof(char *));
	if (!s2)
		return (NULL);
	while (s1[b])
	{
		s2[b] = ft_strdup(s1[b]);
		b++;	
	}
	s2[b] = NULL;
	return (s2);
}

t_cmd	*add_cmd(char **cmd, t_iof *fd)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->cmd = ft_strdup_double(cmd);
	new_cmd->infd = fd->infd;
	new_cmd->outfd = fd->outfd;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*last_node_cmd(t_cmd **env)
{
	t_cmd	*lastnode;

	lastnode = *env;
	while (lastnode->next != NULL)
		lastnode = lastnode->next;
	return (lastnode);
}

void	add_back_cmd(t_cmd **head, char **cmd, t_iof *fd)
{
	t_cmd	*newnode;
	t_cmd	*lastnode;

	if ((*head) == NULL)
		*head = add_cmd(cmd, fd);
	else
	{
		newnode = add_cmd(cmd, fd);
		lastnode = last_node_cmd(head);
		lastnode->next = newnode;
	}	
}
