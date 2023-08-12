/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:37:13 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:04:17 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_cmd(t_all all, t_builtin *arr)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (all.cmd->cmd[a])
		a++;
	all.fd->n_cmd = malloc(sizeof(char *) * (a + 1));
	arr->d = 0;
	while (arr->d < a)
	{
		all.fd->n_cmd[arr->d] = delete_quotes(all.cmd->cmd[b]);
		arr->d++;
		b++;
	}
	all.fd->n_cmd[arr->d] = NULL;
	if ((access(all.fd->n_cmd[0], X_OK) == 0
			&& ft_strncmp(all.fd->n_cmd[0], "./", 2) == 0)
		|| ft_strncmp(all.fd->n_cmd[0], "./", 2) == 0
		|| ft_strncmp(all.fd->n_cmd[0], "/", 1) == 0)
		execv_single_path(all, arr);
	else
		access_single_cmd(all, arr);
}

void	welcome_to_single_excute(t_all all, t_builtin *arr)
{
	free(arr->cmd_ns);
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
	while (waitpid(arr->pid, &arr->exit, 0) != -1)
		;
	if (WIFEXITED(arr->exit))
			g_exit_value = WEXITSTATUS(arr->exit);
}

void	check_single_cmd(t_all all, t_builtin *arr, t_env **new_env)
{
	arr->cmd_ns = delete_quotes(all.cmd->cmd[0]);
	if (all.cmd->cmd[0] == NULL || arr->cmd_ns == NULL)
		return ;
	while (all.cmd->cmd[arr->args])
		arr->args++;
	arr->env_path = check_path_env(*new_env, arr);
	if (ft_strcmp(arr->cmd_ns, "pwd") == 0)
		builtin_pwd(arr);
	else if (ft_strcmp(arr->cmd_ns, "cd") == 0)
		builtin_cd(all.cmd->cmd, *new_env, arr);
	else if (ft_strcmp(arr->cmd_ns, "env") == 0)
		print_env(*new_env, arr);
	else if (ft_strcmp(arr->cmd_ns, "export") == 0)
		builtin_export(*new_env, all.cmd->cmd, arr);
	else if (ft_strcmp(arr->cmd_ns, "exit") == 0)
		builtin_exit(all.cmd->cmd, arr);
	else if (ft_strcmp(arr->cmd_ns, "echo") == 0)
		builtin_echo(all.cmd->cmd, arr);
	else if (ft_strcmp(arr->cmd_ns, "unset") == 0)
		builtin_unset(new_env, arr, all.cmd->cmd);
	else
		welcome_to_single_excute(all, arr);
	ft_free_double(arr->env_path);
}

void	check_io_file_single(t_all all, t_builtin *arr, t_env **new_env)
{
	arr->args = 0;
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
}
