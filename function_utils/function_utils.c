/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 15:24:47 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	a;

	a = 0;
	if (s1[a] == '\0' && s2[a] == '\0')
		return (0);
	else if (s1[a] == '\0' && s2)
		return (-1);
	else if (s1 && s2[a] == '\0')
		return (1);
	while (s1[a] || s2[a])
	{
		if ((unsigned char)s1[a] != (unsigned char)s2[a])
		{
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		}
		a++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

int	check_first_qoutes(char *cmd, t_builtin *arr)
{
	arr->move_b++;
	while (cmd[arr->move_b] != '\"' && cmd[arr->move_b] != '\0')
		arr->move_b++;
	return (arr->move_b);
}

int	check_last_qoutes(char *cmd, t_builtin *arr)
{
	arr->move_b++;
	while (cmd[arr->move_b] != '\'' && cmd[arr->move_b] != '\0')
		arr->move_b++;
	return (arr->move_b);
}

int	check_qoutes(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b] == '\"')
		arr->move_b = check_first_qoutes(cmd, arr);
	else if (cmd[arr->move_b] == '\'')
		arr->move_b = check_last_qoutes(cmd, arr);
	return (arr->move_b);
}

int	check_first_qoutes_red(char *cmd, t_builtin *arr)
{
	arr->str_b++;
	while (cmd[arr->str_b] != '\"' && cmd[arr->str_b] != '\0')
		arr->str_b++;
	return (arr->str_b);
}

int	check_last_qoutes_red(char *cmd, t_builtin *arr)
{
	arr->str_b++;
	while (cmd[arr->str_b] != '\'' && cmd[arr->str_b] != '\0')
		arr->str_b++;
	return (arr->str_b);
}

int	check_qoutes_red(char *cmd, t_builtin *arr)
{
	if (cmd[arr->str_b] == '\"')
		arr->str_b = check_first_qoutes_red(cmd, arr);
	else if (cmd[arr->str_b] == '\'')
		arr->str_b = check_last_qoutes_red(cmd, arr);
	return (arr->str_b);
}
