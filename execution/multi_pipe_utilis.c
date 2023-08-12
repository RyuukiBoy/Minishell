/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:11:03 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:04:09 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_first_null(t_all all, t_builtin *arr)
{
	if (!all.cmd->cmd[0])
	{
		close(arr->p[1]);
		close(arr->p[0]);
		close(arr->her_p[0]);
		close(arr->her_p[1]);
		exit(0);
	}
	if (all.cmd->outfd == -10 && all.cmd->infd == -10)
	{
		g_exit_value = 258;
		exit (258);
	}
	if (all.cmd->infd < 0 || all.cmd->outfd < 0)
	{
		g_exit_value = 1;
		exit(1);
	}
}

void	check_last_cmd(t_all all, t_builtin *arr, t_env **new_env)
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

void	check_first_cmd(t_all all, t_builtin *arr, t_env **new_env)
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

void	check_second_cmd(t_all all, t_builtin *arr, t_env **new_env)
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

void	before_multi_cmd(t_all all, t_builtin *arr, t_env **new_env)
{
	check_first_null(all, arr);
	if (all.cmd->next == NULL)
		check_last_cmd(all, arr, new_env);
	else if (arr->c == 0)
		check_first_cmd(all, arr, new_env);
	else
		check_second_cmd(all, arr, new_env);
}
