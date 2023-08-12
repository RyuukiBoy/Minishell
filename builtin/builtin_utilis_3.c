/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:20:09 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:02:16 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_equal(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	a;
	unsigned int	b;

	a = start;
	b = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	if (start > (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (s[a] && b < len)
	{
		if (s[a] == '+')
			a++;
		p[b] = s[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}

char	*ft_join_utils(char const *s1, char const *s2)
{
	char	*p;

	p = NULL;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
	{
		p = ft_strdup(s2);
		return (p);
	}
	else if (s1 && !s2)
	{
		p = ft_strdup(s1);
		return (p);
	}
	return (p);
}

char	*ft_strjoin_equal(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (ft_join_utils(s1, s2));
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
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}

int	check_char_nor(t_builtin *arr, char **add)
{
	if ((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_' || add[arr->a][arr->b] == '+')
	{
		return (1);
	}
	return (0);
}

int	check_char(t_builtin *arr, char **add, t_env **new_node)
{
	if (check_char_nor(arr, add) == 1)
	{
		if ((add[arr->a][arr->b] == '+' && add[arr->a][arr->b + 1] != '='))
		{
			ft_putstr_fd(add[arr->a], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_exit_value = 1;
			return (-1);
		}
		else if ((add[arr->a][arr->b] == '+' && add[arr->a][arr->b + 1] == '='))
		{
			export_equal(arr, add[arr->a], new_node);
			return (1);
		}
	}
	else
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_exit_value = 1;
		return (-1);
	}
	return (0);
}
