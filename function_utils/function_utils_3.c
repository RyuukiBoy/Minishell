/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:21:40 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:04:21 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_av_ac(int ac, char **av)
{
	if (ac != 1)
	{
		printf("error args %s\n", *av);
		g_exit_value = 1;
		exit(1);
	}
}

int	ft_strlen_double(char *cmd, t_builtin *arr)
{
	arr->str_a = 0;
	while (cmd[arr->str_a])
	{
		if (cmd[arr->str_a] != '<' || cmd[arr->str_a] != '>'
			|| cmd[arr->str_a] == ' ' || cmd[arr->str_a] == '\t'
			|| cmd[arr->str_a] == '\'' || cmd[arr->str_a] == '\"')
			return (2);
		arr->str_a++;
	}
	return (1);
}

int	skip_double_quotes(char const *str, int a)
{
	a = a + 1;
	while (str[a] != '\"' && str[a] != '\0')
		a++;
	return (a);
}

int	skip_single_quotes(char const *str, int a)
{
	a = a + 1;
	while (str[a] != '\'' && str[a] != '\0')
		a++;
	return (a);
}

char	*ft_strjoin_execve(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (0);
	d = (ft_strlen(s1) + ft_strlen(s2) + 2);
	a = 0;
	b = 0;
	p = malloc(d * sizeof(char));
	if (!p)
		return (0);
	while (s1[b] && d - 1 > a)
	{
		p[a] = s1[b];
		a++;
		b++;
	}
	p[a++] = '/';
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}
