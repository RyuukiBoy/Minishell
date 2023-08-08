/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:20:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 15:23:51 by oait-bad         ###   ########.fr       */
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
	//exit_value = 127;
	exit(127);
}

// void	execv_cmd(t_all all, t_builtin *arr, char **cmd)
// {
// 	close(arr->p[0]);
// 	close(arr->p[1]);
// 	arr->exe = execve(arr->fcmd, cmd, arr->env_path);
// 	if (arr->exe == -1) 
// 	{
// 		ft_putstr_fd(*all.cmd->cmd, 2);
// 		write(2, ": Command not found\n", 20);
// 	}
// 	exit(127);
// }

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
	//exit_value = 127;
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

// void	modify_cmd(char *cmd, t_builtin *arr, char *new_cmd)
// {
// 	free(cmd);
// 	cmd = malloc(ft_strlen(new_cmd) + 1);
// 	strcpy(cmd, new_cmd);
// }

// void	access_function(t_all all, t_builtin *arr)
// {
// 	char *cmd;
// 	arr->d = 0;
// 	while (arr->d < arr->a)
// 	{
// 		cmd = delete_quotes(all.cmd->cmd[arr->c]);
// 		modify_cmd(all.cmd->cmd[arr->c], arr, cmd);
// 		arr->d++;
// 	}
// 	//cmd[arr->d] = NULL;
// 	// while (arr->env_path && arr->env_path[arr->b])
// 	// {
// 	// 	arr->fcmd = ft_strjoin_execve(arr->env_path[arr->b], cmd[0]);
// 	// 	if (access(arr->fcmd, X_OK) == 0)
// 	// 		break ;
// 	// 	free(arr->fcmd);
// 	// 	arr->b++;
// 	// }
// 	execv_cmd(all, arr);
// }

char	**check_path_env(t_env *new_env, t_builtin *arr)
{
	char	**n_path;
	char	*b_path;

	arr->a = 0;
	b_path = NULL;
	n_path =  NULL;
	if (new_env == NULL)
		return (NULL);
	while (new_env)
	{
		if (ft_strncmp("PATH=", new_env->name, 5) == 0)
		{
			b_path = new_env->value;
			break ;
		}
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

void	welcome_to_multi(t_all all, t_builtin *arr, t_env **new_env)
{
	arr->args = 0;
	while (all.cmd->cmd[arr->args])
		arr->args++;
	if (ft_strcmp(all.cmd->cmd[0], "pwd") == 0)
	{
		builtin_pwd();
		//exit_value = 0;
	}
	else if (ft_strcmp(all.cmd->cmd[0], "cd") == 0)
	{
		builtin_cd(all.cmd->cmd, *new_env);
		//exit_value = 0;
		exit(0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "env") == 0)
	{
		print_env(*new_env);
		//exit_value = 0;
		exit(0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "export") == 0)
	{
		builtin_export(*new_env, all.cmd->cmd, arr);
		//exit_value = 0;
		exit(0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "echo") == 0)
	{
		builtin_echo(all.cmd->cmd, arr->args, arr);
		//exit_value = 0;
		exit(0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "unset") == 0)
	{
		builtin_unset(new_env, arr, all.cmd->cmd);
		//exit_value = 0;
		exit(0);
	}
	else if (ft_strcmp(all.cmd->cmd[0], "exit") == 0)
	{
		dup2(arr->output, 1);
		dup2(arr->input, 0);
		builtin_exit_multi(all.cmd->cmd, arr);
	}
	else
		access_path(all, arr);
}

void	before_multi_cmd(t_all all, t_builtin *arr, t_env **new_env)
{
	dprintf(2, "====%s===\n", all.cmd->cmd[0]);
	if(!all.cmd->cmd[0]){
		close(arr->p[1]);
		close(arr->p[0]);
		close(arr->her_p[0]);
		close(arr->her_p[1]);
		exit(0);
	}
	if (all.cmd->outfd == -10 && all.cmd->infd == -10)
	{
		//exit_value = 258;
		exit (258);
	}
	if (all.cmd->infd < 0 || all.cmd->outfd < 0)
	{
		//exit_value = 1;
		exit(1);
	}
	if (all.cmd->next == NULL)
	{
		if (all.cmd->infd > 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd > 1)
				dup2(all.cmd->outfd, 1);
			else
				dup(arr->output);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd > 1)
				dup2(all.cmd->outfd, 1);
			welcome_to_multi(all, arr, new_env);
		}
	}
	else if (arr->c == 0)
	{
		if (all.cmd->infd > 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd > 1)
				dup2(all.cmd->outfd, 1);
			else
			 	dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd > 1)
				 dup2(all.cmd->outfd, 1);
			else
				dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
	}
	else
	{
		if (all.cmd->infd > 0)
		{
			dup2(all.cmd->infd, 0);
			if (all.cmd->outfd > 1)
				dup2(all.cmd->outfd, 1);
			else
				dup2(arr->p[1], 1);
			welcome_to_multi(all, arr, new_env);
		}
		else
		{
			if (all.cmd->outfd > 1)
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
	if (all.cmd->infd != 0)
		close(all.cmd->infd);
	if (all.cmd->outfd != 1)
		close(all.cmd->outfd);
	close(arr->p[0]);
	close(arr->p[1]);
}

int	welcome_to_multi_v2(t_all all, t_builtin *arr, t_env **new_env)
{
	if (pipe(arr->p) == -1)
		perror("pipe:");
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork:");
	if (arr->pid == 0)
	 	before_multi_cmd(all, arr, new_env);
	else
		parent_cmd(all, arr);
	return (arr->pid);
}

void	multi_cmd(t_all all, t_builtin *arr, t_env **new_env)
{
	arr->env_path = check_path_env(*new_env, arr);
	arr->exitstatus = malloc((size_list_cmd(all.cmd, arr) + 1) * (sizeof(int)));
	arr->exitarray = malloc((size_list_cmd(all.cmd, arr) + 1) * (sizeof(int)));
	arr->c = 0;
	arr->d = 0;
	while (all.cmd)
	{
		dup2(arr->output , 1);
		arr->exitarray[arr->c] = welcome_to_multi_v2(all, arr, new_env);
		all.cmd = all.cmd->next;
		arr->c++;
	}
	while (waitpid(arr->exitarray[arr->d], &arr->exit, 0) != -1)
	{
		if (WIFEXITED(arr->exit))
			arr->exitstatus[arr->d] = WEXITSTATUS(arr->exit);
		arr->d++;
	}
	//exit_value = arr->exitstatus[arr->d];
}

void	check_cmd(char **b_cmd, t_builtin *arr, t_env **new_env)
{
	char	**n_cmd;
	t_all	all;

	all.fd = (t_iof *)malloc(sizeof(t_iof));
	all.fd->infd = 0;
	all.fd->outfd = 1;
	all.cmd = NULL;
	arr->c = 0;
	while (b_cmd[arr->c])
	{
		b_cmd[arr->c] = any_cmd(b_cmd[arr->c], arr, all);
		n_cmd = ft_split_space(b_cmd[arr->c], ' ');
		add_back_cmd(&all.cmd ,n_cmd, all.fd);
		ft_free_double(n_cmd);
		arr->c++;
	}
	free(all.fd);
	ft_free_double(b_cmd);
	if (size_list_cmd(all.cmd, arr) == 1)
		check_io_file_single(all, arr, new_env);
	else
		multi_cmd(all, arr, new_env);
}
