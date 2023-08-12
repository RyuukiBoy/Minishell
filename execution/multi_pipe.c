/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:20:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 14:45:33 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	access_path(t_all all, t_builtin *arr)
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
		execv_path(all, arr);
	else
		access_function(all, arr);
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
		arr->exitarray[arr->c] = welcome_to_multi_v2(all, arr, new_env);
		all.cmd = all.cmd->next;
		arr->c++;
	}
	ft_free_double(arr->env_path);
	while (waitpid(arr->exitarray[arr->d], &arr->exit, 0) != -1)
	{
		if (WIFEXITED(arr->exit))
			arr->exitstatus[arr->d] = WEXITSTATUS(arr->exit);
		arr->d++;
	}
	g_exit_value = arr->exitstatus[arr->d];
	free(arr->exitstatus);
	free(arr->exitarray);
}

void	check_cmd(char **b_cmd, t_builtin *arr, t_env **new_env)
{
	char	**n_cmd;
	t_all	all;

	all.fd = (t_iof *)malloc(sizeof(t_iof));
	all.fd->n_cmd = NULL;
	all.fd->infd = 0;
	all.fd->outfd = 1;
	all.cmd = NULL;
	arr->c = 0;
	while (b_cmd[arr->c])
	{
		b_cmd[arr->c] = any_cmd(b_cmd[arr->c], arr, all);
		if (arr->here_exit == 1)
			return ;
		n_cmd = ft_split_space(b_cmd[arr->c], ' ');
		add_back_cmd(&all.cmd, n_cmd, all.fd);
		ft_free_double(n_cmd);
		arr->c++;
	}
	ft_free_double(b_cmd);
	if (size_list_cmd(all.cmd, arr) == 1)
		check_io_file_single(all, arr, new_env);
	else
		multi_cmd(all, arr, new_env);
	free_iof(all.fd);
	free_cmd(all.cmd);
}
