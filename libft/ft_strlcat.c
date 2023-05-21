/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:41:57 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:53:49 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{	
	unsigned int	i;
	unsigned int	j;
	unsigned int	dlen;
	unsigned int	slen;

	slen = ft_strlen(src);
	if (!dest && !len)
		return (slen);
	dlen = ft_strlen(dest);
	i = 0;
	j = dlen;
	if (len == 0 || len <= dlen)
		return (len + slen);
	while (src[i] && i < len - j - 1)
	{
		dest[dlen] = src[i];
		i++;
		dlen++;
	}
	dest[dlen] = '\0';
	return (j + slen);
}
