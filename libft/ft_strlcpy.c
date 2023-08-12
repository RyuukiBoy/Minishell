/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:34:10 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:53:53 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dstsize - 1 > a && src[a])
	{
		dst[b] = src[a];
		a++;
		b++;
	}
	dst[b] = '\0';
	return (ft_strlen(src));
}
