/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_utilis_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:48:04 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:04:03 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execv_cmd_path(t_all all, t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(all.fd->n_cmd[0], all.fd->n_cmd, arr->env_path);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.fd->n_cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	g_exit_value = 127;
	exit(127);
}

void	execv_path(t_all all, t_builtin *arr)
{
	if (ft_strncmp(all.fd->n_cmd[0], "./", 2) == 0)
	{
		if (access(all.fd->n_cmd[0], R_OK) == 0)
		{
			close(arr->p[0]);
			close(arr->p[1]);
			arr->exe = execve(all.fd->n_cmd[0], all.fd->n_cmd, arr->env_path);
			if (arr->exe == -1)
			{
				ft_putstr_fd(*all.fd->n_cmd, 2);
				write(2, ": Permission denied\n", 20);
			}
			g_exit_value = 126;
			exit(126);
		}
	}
	else
		execv_cmd_path(all, arr);
}

void	execv_cmd(t_all all, t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(arr->fcmd, all.fd->n_cmd, arr->env_path);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.fd->n_cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	g_exit_value = 127;
	exit(127);
}

void	free_cmd(t_cmd *head)
{
	int		i;
	t_cmd	*temp;

	while (head != NULL)
	{
		temp = head;
		if (temp->cmd != NULL)
		{
			i = 0;
			while (temp->cmd[i] != NULL)
			{
				free(temp->cmd[i]);
				i++;
			}
			free(temp->cmd);
		}
		head = head->next;
		free(temp);
	}
}

void	free_iof(t_iof *iof)
{
	int	i;

	if (iof == NULL)
		return ;
	if (iof->n_cmd != NULL)
	{
		i = 0;
		while (iof->n_cmd[i] != NULL)
		{
			free(iof->n_cmd[i]);
			i++;
		}
		free(iof->n_cmd);
	}
	free(iof);
}
