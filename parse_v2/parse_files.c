/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:49 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/12 20:03:18 by ybargach         ###   ########.fr       */
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

void	file_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

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

char	*space_limt(char *cmd)
{
	char	*p;
	int		a;
	int		b;

	a = 0;
	b = 0;
	p = malloc(ft_strlen_int(cmd) + 1);
	if (p == NULL)
		return (NULL);
	while (cmd[a])
	{
		if (cmd[a + 1] == '\0' && (cmd[a] == ' ' || cmd[a] == '\t'))
			break ;
		p[b] = cmd[a];
		b++;
		a++;
	}
	p[b] = '\0';
	return (p);
}
