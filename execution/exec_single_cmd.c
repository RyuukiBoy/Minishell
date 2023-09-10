/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:48:43 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 18:09:14 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_path_cmd(t_all all, t_builtin *arr)
{
	arr->exe = execve(all.fd->n_cmd[0], all.fd->n_cmd, arr->env_v);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.fd->n_cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	g_exit_value = 127;
	exit(127);
}

void	execv_single_path(t_all all, t_builtin *arr)
{
	if (ft_strncmp(all.fd->n_cmd[0], "./", 2) == 0)
	{
		if (access(all.fd->n_cmd[0], R_OK) == 0)
		{
			arr->exe = execve(all.fd->n_cmd[0], all.fd->n_cmd, arr->env_v);
			if (arr->exe == -1)
			{
				ft_putstr_fd(*all.fd->n_cmd, 2);
				write(2, ": Permission denied\n", 20);
			}
			g_exit_value = 126;
			exit(126);
		}
		else
		{
			ft_putstr_fd(*all.fd->n_cmd, 2);
			write(2, ": No such file or directory\n", 28);
			g_exit_value = 127;
			exit(127);
		}
	}
	else
		execve_path_cmd(all, arr);
}

void	execve_cmd(t_all all, t_builtin *arr)
{
	arr->exe = execve(arr->fcmd, all.fd->n_cmd, arr->env_v);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.fd->n_cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	g_exit_value = 127;
	exit(127);
}

void	access_single_cmd(t_all all, t_builtin *arr)
{
	arr->b = 0;
	while (arr->env_path && arr->env_path[arr->b])
	{
		arr->fcmd = ft_strjoin_execve(arr->env_path[arr->b], all.fd->n_cmd[0]);
		if (access(arr->fcmd, X_OK) == 0)
			break ;
		free(arr->fcmd);
		arr->b++;
	}
	execve_cmd(all, arr);
}
