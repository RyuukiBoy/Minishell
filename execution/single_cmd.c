/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:37:13 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 14:34:15 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	access_single_cmd(t_all all, t_builtin *arr)
{
	arr->b = 0;
	while (arr->env_path && arr->env_path[arr->b])
	{
		arr->fcmd = ft_strjoin_execve(arr->env_path[arr->b], all.cmd->cmd[0]);
		if (access(arr->fcmd, X_OK) == 0)
			break ;
		free(arr->fcmd);
		arr->b++;
	}
	execve_cmd(all, arr);
}

void	single_cmd(t_all all, t_builtin *arr)
{
	if ((access(all.cmd->cmd[0], X_OK) == 0 && ft_strncmp(all.cmd->cmd[0], "./", 2) == 0)
		|| ft_strncmp(all.cmd->cmd[0], "./", 2) == 0
		|| ft_strncmp(all.cmd->cmd[0], "/" , 1) == 0)
		execve_path_cmd(all, arr);
	else
		access_single_cmd(all, arr);
}

void	welcome_to_single_excute(t_all all, t_env *new_env, t_builtin *arr)
{
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork: ");
	if (arr->pid == 0)
		single_cmd(all, arr);
	else
	{
		if (all.cmd->infd != 0)
			close(all.cmd->infd);
		if (all.cmd->outfd != 1)
			close(all.cmd->outfd);
	}
}

void	check_single_cmd(t_all all, t_builtin *arr, t_env **new_env)
{
	if (all.cmd->cmd[0] == NULL)
		return ;
	arr->args = 0;
	while (all.cmd->cmd[arr->args])
		arr->args++;
	arr->env_path = check_path_env(*new_env, arr);
	if (ft_strcmp(all.cmd->cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(all.cmd->cmd[0], "cd") == 0)
		builtin_cd(all.cmd->cmd, *new_env);
	else if (ft_strcmp(all.cmd->cmd[0], "env") == 0)
		print_env(*new_env);
	else if (ft_strcmp(all.cmd->cmd[0], "export") == 0)
		builtin_export(*new_env, all.cmd->cmd, arr);
	else if (ft_strcmp(all.cmd->cmd[0], "exit") == 0)
		builtin_exit(all.cmd->cmd, arr);
	else if (ft_strcmp(all.cmd->cmd[0], "echo") == 0)
		builtin_echo(all.cmd->cmd, arr->args, arr);
	else if (ft_strcmp(all.cmd->cmd[0], "unset") == 0)
		builtin_unset(new_env, arr, all.cmd->cmd);
	else
		welcome_to_single_excute(all, *new_env, arr);
}

void	check_io_file_single(t_all all, t_builtin *arr, t_env **new_env)
{
	if (all.cmd->infd < 0 || all.cmd->outfd < 0)
		return ;
	if (all.cmd->infd != 0)
	{
		dup2(all.cmd->infd, 0);
		if (all.cmd->outfd != 1)
			dup2(all.cmd->outfd, 1);
		else
			dup(arr->output);
		check_single_cmd(all, arr, new_env);
	}
	else
	{
		if (all.cmd->outfd != 1)
			dup2(all.cmd->outfd, 1);
		check_single_cmd(all, arr, new_env);
	}
	while (wait(NULL) != -1);
}
