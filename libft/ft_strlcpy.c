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

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = ft_strlen(src);
	if (len != 0)
	{
		while (src[x] && x < len - 1)
		{
			dest[x] = src[x];
			x++;
		}
		dest[x] = '\0';
	}
	return (y);
}
