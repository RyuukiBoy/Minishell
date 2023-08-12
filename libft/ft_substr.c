/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:31:13 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/11 17:23:27 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
		p[b] = s[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}

static size_t	ft_min(unsigned long long a, unsigned long long b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr_simple(char const *s, unsigned int start, size_t len)
{
	char			*d;
	size_t			i;
	unsigned int	size;

	if (!s)
		return (0);
	size = ft_strlen(s) + 1;
	i = 0;
	if (start >= size)
		return (ft_strdup("\0"));
	len = ft_min(size - start, len);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (0);
	while (i < len)
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
