/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:35:46 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/09 13:38:01 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_double_space(char const *str, int a)
{
	a = a + 1;
	while (str[a] != '\"' && str[a + 1])
		a++;
	return (a);
}

int	skip_single_space(char const *str, int a)
{
	a = a + 1;
	while (str[a] != '\'' && str[a + 1])
		a++;
	return (a);
}

int	check_qoutes(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b] == '\"')
		arr->move_b = check_first_qoutes(cmd, arr);
	else if (cmd[arr->move_b] == '\'')
		arr->move_b = check_last_qoutes(cmd, arr);
	return (arr->move_b);
}

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
