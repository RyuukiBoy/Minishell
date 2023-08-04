/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:48:43 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 10:47:27 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_path_cmd(t_all all, t_builtin *arr)
{
	arr->exe = execve(all.cmd->cmd[0], all.cmd->cmd, arr->env_path);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.cmd->cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	exit(127);
}

void	execve_cmd(t_all all, t_builtin *arr)
{
	arr->exe = execve(arr->fcmd, all.cmd->cmd, arr->env_path);
	if (arr->exe == -1) {
		ft_putstr_fd(*all.cmd->cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	exit(127);
}
