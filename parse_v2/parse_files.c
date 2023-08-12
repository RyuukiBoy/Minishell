/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:49 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/12 09:02:50 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name_file(char *cmd)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (cmd[a])
	{
		if (cmd[a] == '\"' || cmd[a] == '\'')
			a = check_qoutes_file(cmd, a);
		else if (cmd[a] == ' ' || cmd[a] == '\t')
			break ;
		else if (check_opera_file(cmd, a) == 0)
		{
			file_error(cmd);
			b = -1;
			break ;
		}
		a++;
	}
	return (b);
}

int	check_opera_file(char *cmd, int a)
{
	if (cmd[a] >= 42 && cmd[a] <= 45)
		return (1);
	else if (cmd[a] >= 48 && cmd[a] <= 58)
		return (1);
	else if (cmd[a] >= 63 && cmd[a] <= 91)
		return (1);
	else if (cmd[a] >= 93 && cmd[a] <= 95)
		return (1);
	else if (cmd[a] >= 97 && cmd[a] <= 123)
		return (1);
	else if (cmd[a] == 33 || cmd[a] == 61
		|| cmd[a] == 125 || cmd[a] == '\0')
		return (1);
	return (0);
}

void	more_norm(t_all all, char *b_limir)
{
	all.fd->infd = open(b_limir, O_RDONLY);
	if (all.fd->infd == -1)
		file_err(b_limir);
	free(b_limir);
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

	a = 0;
	c = check_name_file(cmd[1]);
	if (c == -1)
	{
		all.fd->outfd = -10;
		all.fd->infd = -10;
		return ;
	}
	b_limir = delete_quotes(cmd[1]);
	redir_for_norm(cmd, arr, all, b_limir);
}
