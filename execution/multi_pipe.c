/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:20:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 14:53:10 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execv_cmd(t_all all, t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(arr->fcmd, all.cmd->cmd, arr->env_path);
	if (arr->exe == -1) {
		ft_putstr_fd(*all.cmd->cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	exit(127);
}

void	execv_path(t_all all, t_builtin *arr)
{
	close(arr->p[0]);
	close(arr->p[1]);
	arr->exe = execve(all.cmd->cmd[0], all.cmd->cmd, arr->env_path);
	if (arr->exe == -1)
	{
		ft_putstr_fd(*all.cmd->cmd, 2);
		write(2, ": Command not found\n", 20);
	}
	exit(127);
}

void	access_function(t_all all, t_builtin *arr)
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
	execv_cmd(all, arr);
}
char	**check_path_env(t_env *new_env, t_builtin *arr)
{
	char	**n_path;
	char	*b_path;

	arr->a = 0;
	while (new_env)
	{
		if (ft_strncmp("PATH=", new_env->name, 5) == 0)
			b_path = new_env->value;
		new_env = new_env->next;
	}
	n_path = ft_split(b_path, ':');
	return (n_path);
}

void	access_path(t_all all, t_builtin *arr)
{
	if ((access(all.cmd->cmd[0], X_OK) == 0 && ft_strncmp(all.cmd->cmd[0], "./", 2) == 0)
		|| ft_strncmp(all.cmd->cmd[0], "./", 2) == 0
		|| ft_strncmp(all.cmd->cmd[0], "/" , 1) == 0)
		execv_path(all, arr);
	else
		access_function(all, arr);
}

void	welcome_to_multi(t_all all, t_builtin *arr, t_env *new_env)
{
	arr->args = 0;
	while (all.cmd->cmd[arr->args])
		arr->args++;
	arr->env_path = check_path_env(new_env, arr);
	if (ft_strcmp(all.cmd->cmd[0], "pwd") == 0)
	{
		builtin_pwd();
		exit (0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "cd") == 0)
	{
		builtin_cd(all.cmd->cmd);
		exit (0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "env") == 0)
	{
		print_env(new_env);
		exit (0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "export") == 0)
	{
		builtin_export(new_env, all.cmd->cmd, arr);
		exit (0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "echo") == 0)
	{
		builtin_echo(all.cmd->cmd, arr->args, arr);
		exit (0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "unset") == 0)
	{
		builtin_unset(new_env, arr, all.cmd->cmd);
		exit (0);
	}
	else
		access_path(all, arr);
}

void	before_multi_cmd(t_all all, t_builtin *arr, t_env *new_env, char **cmd)
{
	if (all.cmd->next == NULL)
	{
		if (all.cmd->infd != 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd != 1){
				dup2(all.cmd->outfd, 1);}
			else
				dup(arr->output);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd != 1)
				dup2(all.cmd->outfd, 1);
			welcome_to_multi(all, arr, new_env);
		}
	}
	else if (arr->c == 0)
	{
		if (all.cmd->infd != 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd != 1)
				dup2(all.cmd->outfd, 1);
			else
			 	dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd != 1)
				 dup2(all.cmd->outfd, 1);
			else
				dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
	}
	else
	{
		if (all.cmd->infd != 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd != 1)
				dup2(all.cmd->outfd, 1);
			else
				dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd != 1)
				 dup2(all.cmd->outfd, 1);
			else
				dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
	}
}

void	parent_cmd(t_all all, t_builtin *arr)
{
	dup2(arr->p[0], 0);
	if (all.fd->infd != 0)
		close(all.fd->infd);
	if (all.fd->outfd != 1)
		close(all.fd->outfd);
	close(arr->p[0]);
	close(arr->p[1]);
}

void	welcome_to_multi_v2(t_all all, t_builtin *arr, t_env *new_env, char **cmd)
{
	if (pipe(arr->p) == -1)
		perror("pipe:");
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork:");
	if (arr->pid == 0)
	 	before_multi_cmd(all, arr, new_env, cmd);
	else
		parent_cmd(all, arr);
}

void	multi_cmd(t_all all, t_builtin *arr, t_env *new_env, char **b_cmd)
{
	arr->c = 0;
	while (all.cmd)
	{
		dup2(arr->output , 1);
		welcome_to_multi_v2(all, arr, new_env, b_cmd);
		all.cmd = all.cmd->next;
		arr->c++;
	}
	while (wait(NULL) != -1);
}

void	check_cmd(char **b_cmd, t_builtin *arr, t_env *new_env)
{
	char	**n_cmd;
	t_all	all;

	all.fd = (t_iof *)malloc(sizeof(t_iof));
	all.fd->infd = 0;
	all.fd->outfd = 1;
	all.cmd = NULL;
	arr->input = dup(0);
	arr->output = dup(1);
	arr->space = size_list(&new_env, arr);
	arr->env = put_env_array(&new_env, arr, arr->space);
	arr->full_path = check_env_path(&new_env, arr);
	arr->c = 0;
	while (b_cmd[arr->c])
	{
		b_cmd[arr->c] = any_cmd(b_cmd[arr->c], arr, all.fd);
		n_cmd = ft_split(b_cmd[arr->c], ' ');
		add_back_cmd(&all.cmd ,n_cmd, all.fd);
		ft_free_double(n_cmd);
		arr->c++;
	}
	free(all.fd);
	ft_free_double(b_cmd);
	if (size_list_cmd(all.cmd, arr) == 1)
		check_single_cmd(all, arr, new_env);
	else
		multi_cmd(all, arr, new_env, b_cmd);
}
