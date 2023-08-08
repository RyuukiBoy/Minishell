/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 09:34:17 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/06 15:51:28 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	words(char const *str, char c)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[a])
	{
		while (str[a] == c && str[a])
			a++;
		while (str[a] != c && str[a])
		{
			if (str[a] == '\"')
			a = skip_double_quotes(str, a);
			else if (str[a] == '\'')
			a = skip_single_quotes(str, a);
			if (str[a] == '\0')
				break ;
			a++;
		}
		count++;
	}
	return (count);
}

static int	start_quotes(char *str, char c, int i)
{
	while (str[i] == c && str[i])
	{
		i++;
	}
	return (i);
}

static int	end_qoutes(char *str, char c, int i)
{
	while (str[i] != c && str[i])
	{
		if (str[i] == '\"')
		{
			i = i + 1;
			while (str[i] != '\"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			i = i + 1;
			while (str[i] != '\'' && str[i])
				i++;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

static char	*trim_qoutes(char const *s, char c)
{
	char	*t;
	char	*str;

	if (!s)
		return (0);
	t = (char *)malloc(2 * sizeof(char));
	if (!t)
		return (0);
	t[0] = c;
	t[1] = '\0';
	str = ft_strtrim(s, t);
	free(t);
	return (str);
}

char	**ft_split_qoutes(char const *s, char c)
{
	char	**p;
	char	*str;
	int		b;
	int		x;
	int		y;

	if (!s)
		return (0);
	str = trim_qoutes(s, c);
	b = 0;
	x = 0;
	y = 0;
	p = (char **)malloc((words(str, c) + 1) * sizeof(char *));
	if (!p || !str)
		return (0);
	while (b < words(str, c))
	{
		x = start_quotes(str, c, y);
		y = end_qoutes(str, c, x);
		p[b] = ft_substr(str, x, (y - x));
		b++;
	}
	p[b] = NULL;
	free(str);
	return (p);
}
