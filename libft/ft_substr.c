/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:31:13 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:54:38 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(unsigned long long a, unsigned long long b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
