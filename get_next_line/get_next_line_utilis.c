/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:36:01 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/14 09:46:47 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr_get(char *str, int c)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
	{
		if (str[a] == c)
			return (str + a);
		a++;
	}
	return (0);
}

int	ft_strlen_get(const char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
		a++;
	return (a);
}

char	*ft_strdup_get(char *str)
{
	int		a;
	int		b;
	char	*p;

	if (!str)
		return (NULL);
	p = malloc((ft_strlen_get(str) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	a = 0;
	b = 0;
	while (str[a])
		p[b++] = str[a++];
	p[b] = '\0';
	return (p);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	int		a;
	int		b;
	int		c;
	char	*p;

	if (!s1 && s2)
		return (ft_strdup_get(s2));
	if (s1 && !s2)
		return (ft_strdup_get(s1));
	if (!s1 && !s2)
		return (NULL);
	a = ft_strlen_get(s1) + ft_strlen_get(s2) + 1;
	p = malloc(a * sizeof(char));
	if (!p)
		return (NULL);
	b = 0;
	c = 0;
	while (s1[b])
		p[c++] = s1[b++];
	b = 0;
	while (s2[b])
		p[c++] = s2[b++];
	p[c] = '\0';
	free(s1);
	return (p);
}
