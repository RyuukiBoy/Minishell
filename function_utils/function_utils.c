/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fucntion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/07/28 11:52:52 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	a;

	a = 0;
	while (s1[a] || s2[a])
	{
		if (!((unsigned char)s1[a] == (unsigned char)s2[a]))
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		a++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	a;

	a = 0;
	while (n > a && (s1[a] || s2[a]))
	{
		if (!((unsigned char)s1[a] == (unsigned char)s2[a]))
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		a++;
	}
	return (0);
}

void	check_first_qoutes(char **cmd, int b, t_builtin *arr)
{
	if ((cmd[arr->i][arr->j] == '"') || (cmd[arr->i][arr->j] == '\''))
	{
			printf("here%c\n", cmd[arr->i][arr->j + 1]);
		if(cmd[arr->i][arr->j + 1] == ' ' || cmd[arr->i][arr->j + 1] == '\t')
		{
			printf("%s: command not found\n", cmd[arr->c]);
			exit(127);
		}
		b++;
	}
}

void	check_last_qoutes(char **cmd, int c, t_builtin *arr)
{
	if((cmd[arr->i][arr->j] == '"') || (cmd[arr->i][arr->j] == '\''))
	{
		if (cmd[arr->i][arr->j - 1] == ' ')
		{
			printf("%s: command not found\n", cmd[arr->c]);
			exit(127);
		}
		c++;
	}
}

void	check_qoutes(char *cmd, t_builtin *arr)
{
	int	b;
	int	c;

	b = 0;
	c = 0;
	arr->i = 0;
	while (cmd[arr->i])
	{

		if (cmd[arr->i] == ' ')
		{
			printf("%s: command not found\n", cmd);
			exit(127);
		}
		arr->i++;
	}
}
