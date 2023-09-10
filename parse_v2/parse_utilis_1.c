/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:55:52 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 20:13:23 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_norm(t_all all, t_builtin *arr, char *b_limir)
{
	all.fd->infd = here_doc(arr, b_limir);
	arr->here_fd[arr->arr_fd] = all.fd->infd;
	arr->arr_fd++;
	return ;
}

void	redir_for_norm(char **cmd, t_builtin *arr, t_all all, char *b_limir)
{
	if (ft_strcmp(cmd[0], ">") == 0)
	{
		all.fd->outfd = open(b_limir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (all.fd->outfd == -1)
			file_err(b_limir);
		free(b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], ">>") == 0)
	{
		all.fd->outfd = open(b_limir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (all.fd->outfd == -1)
			file_err(b_limir);
		free(b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], "<") == 0)
	{
		more_norm(all, b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], "<<") == 0)
		here_norm(all, arr, b_limir);
}

void	redirect(char **cmd, t_builtin *arr, t_all all)
{
	int		a;
	int		c;
	char	*b_limir;
	char	*p;

	a = 0;
	c = check_name_file(cmd[1]);
	if (c == -1)
	{
		all.fd->outfd = -10;
		all.fd->infd = -10;
		return ;
	}
	b_limir = delete_quotes(cmd[1]);
	p = space_limt(b_limir);
	free(b_limir);
	redir_for_norm(cmd, arr, all, p);
}

void	more_norm(t_all all, char *b_limir)
{
	all.fd->infd = open(b_limir, O_RDONLY);
	if (all.fd->infd == -1)
		file_err(b_limir);
	free(b_limir);
}
