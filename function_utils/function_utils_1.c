/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:16:08 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/06 11:14:19 by ybargach         ###   ########.fr       */
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

static int	wordspa(char const *str, char c)
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
				a = skip_double_space(str, a);
			else if (str[a] == '\'')
				a = skip_single_space(str, a);
			a++;
		}
		count++;
	}
	return (count);
}

static int	start_space(char *str, char c, int i)
{
	while (str[i] == c && str[i])
	{
		i++;
	}
	return (i);
}

static int	end_space(char *str, char c, int i)
{
	while (str[i] != c && str[i])
	{

		if (str[i] == '\"')
		{
			i = i + 1;
			while (str[i] != '\"' && str[i + 1])
				i++;
		}
		else if (str[i] == '\'')
		{
			i = i + 1;
			while (str[i] != '\'' && str[i + 1])
				i++;
		}
		i++;
	}
	return (i);
}

static char	*trim_space(char const *s, char c)
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

char	**ft_split_space(char const *s, char c)
{
	char	**p;
	char	*str;
	int		b;
	int		x;
	int		y;

	if (!s)
		return (0);
	str = trim_space(s, c);
	b = 0;
	x = 0;
	y = 0;
	p = (char **)malloc((wordspa(str, c) + 1) * sizeof(char *));
	if (!p || !str)
		return (0);
	while (b < wordspa(str, c))
	{
		x = start_space(str, c, y);
		y = end_space(str, c, x);
		p[b] = ft_substr(str, x, (y - x));
		b++;
	}
	p[b] = NULL;
	free(str);
	return (p);
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
