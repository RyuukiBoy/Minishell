/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:49 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/07 22:30:19 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_err(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	check_first_qoutes_file(char *cmd, int a)
{
	a++;
	while (cmd[a] != '\"' && cmd[a] != '\0')
		a++;
	return (a);
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

int	check_last_qoutes_file(char *cmd, int a)
{
	a++;
	while (cmd[a] != '\'' && cmd[a] != '\0')
	{
		a++;
	}
	return (a);
}

int	check_qoutes_file(char *cmd, int a)
{
	if (cmd[a] == '\"')
		a = check_first_qoutes_file(cmd, a);
	else if (cmd[a] == '\'')
		a = check_last_qoutes_file(cmd, a);
	return (a);
}

void	file_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token " , 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

int	check_name_file(char *cmd)
{
	int a;
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

void	redirect(char **cmd, t_builtin *arr, t_all all)
{
	int		a;
	int		c;
	char	*b_limir;
	char	**limit;

	a = 0;
	c = check_name_file(cmd[1]);
	if (c == -1)
	{
		all.fd->outfd = -10;
		all.fd->infd = -10;
		return ;
	}
	b_limir = delete_quotes(cmd[1]);
	free(cmd[1]);
	if (ft_strcmp(cmd[0], ">") == 0)
	{
		all.fd->outfd = open(b_limir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (all.fd->outfd == -1)
			file_err(b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], ">>") == 0)
	{
		all.fd->outfd = open(b_limir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (all.fd->outfd == -1)
			file_err(b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], "<") == 0)
	{
		all.fd->infd = open(b_limir, O_RDONLY);
		if (all.fd->infd == -1)
			file_err(b_limir);
		return ;
	}
	else if (ft_strcmp(cmd[0], "<<") == 0)
	{
		all.fd->infd = here_doc(arr, all, b_limir);
		return ;
	}
}
