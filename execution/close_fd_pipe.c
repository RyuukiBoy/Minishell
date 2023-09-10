/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:44:12 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 22:06:45 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_fd(t_builtin *arr)
{
	arr->a = 0;
	while (arr->a < arr->arr_fd)
	{
		close(arr->here_fd[arr->a]);
		arr->a++;
	}
}

void	exit_all_fd(t_builtin *arr, t_all all, char **b_cmd, char **n_cmd)
{
	arr->a = 0;
	while (arr->a < arr->arr_fd)
	{
		close(arr->p[0]);
		close(arr->p[1]);
		close_all_fd(arr);
		free_iof(all.fd);
		close(arr->here_fd[arr->a]);
		arr->a++;
	}
	ft_free_double(n_cmd);
	ft_free_double(b_cmd);
}

void	check_cmd_norm(t_builtin *arr, t_env **new_env, t_all all)
{
	if (size_list_cmd(all.cmd, arr) == 1)
		check_io_file_single(all, arr, new_env);
	else
		multi_cmd(all, arr, new_env);
	close_all_fd(arr);
	free_iof(all.fd);
	free_cmd(all.cmd);
}
