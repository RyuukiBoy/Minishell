/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_ulitis_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:29:00 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:03:52 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	access_function(t_all all, t_builtin *arr)
{
	while (arr->env_path && arr->env_path[arr->b])
	{
		arr->fcmd = ft_strjoin_execve(arr->env_path[arr->b], all.fd->n_cmd[0]);
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
	b_path = NULL;
	n_path = NULL;
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

void	welcome_to_multi_seco(t_all all, t_builtin *arr)
{
	if (ft_strcmp(arr->cmd_ns, "exit") == 0)
	{
		dup2(arr->output, 1);
		dup2(arr->input, 0);
		builtin_exit_multi(all.cmd->cmd, arr);
		exit(g_exit_value);
	}
	else if (ft_strcmp(arr->cmd_ns, "pwd") == 0)
	{
		builtin_pwd(arr);
		exit(g_exit_value);
	}
	else
	{
		free(arr->cmd_ns);
		access_path(all, arr);
	}
}

void	welcome_to_multi_first(t_all all, t_builtin *arr, t_env **new_env)
{
	if (ft_strcmp(arr->cmd_ns, "export") == 0)
	{
		builtin_export(*new_env, all.cmd->cmd, arr);
		exit(g_exit_value);
	}
	else if (ft_strcmp(arr->cmd_ns, "echo") == 0)
	{
		builtin_echo(all.cmd->cmd, arr);
		exit(g_exit_value);
	}
	else if (ft_strcmp(arr->cmd_ns, "unset") == 0)
	{
		builtin_unset(new_env, arr, all.cmd->cmd);
		exit(g_exit_value);
	}
	else
		welcome_to_multi_seco(all, arr);
}

void	welcome_to_multi(t_all all, t_builtin *arr, t_env **new_env)
{
	arr->cmd_ns = delete_quotes(all.cmd->cmd[0]);
	arr->args = 0;
	while (all.cmd->cmd[arr->args])
		arr->args++;
	if (ft_strcmp(arr->cmd_ns, "cd") == 0)
	{
		builtin_cd(all.cmd->cmd, *new_env, arr);
		exit(g_exit_value);
	}
	else if (ft_strcmp(arr->cmd_ns, "env") == 0)
	{
		print_env(*new_env, arr);
		exit(g_exit_value);
	}
	else
		welcome_to_multi_first(all, arr, new_env);
}
