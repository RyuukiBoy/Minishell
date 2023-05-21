/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:00:34 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:52:39 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*csrc;
	unsigned char	*cdest;

	i = 0;
	csrc = (unsigned char *) src;
	cdest = (unsigned char *) dest;
	if (!cdest && !csrc)
		return (0);
	if (cdest == csrc)
		return (cdest);
	if (csrc > cdest)
		return (ft_memcpy(cdest, csrc, len));
	while (len--)
	{
		cdest[len] = csrc[len];
	}
	return (dest);
}
