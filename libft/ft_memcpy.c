/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:32:36 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:52:33 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{	
	size_t		i;
	char		*csrc;
	char		*cdest;

	i = 0;
	csrc = (char *) src;
	cdest = (char *) dest;
	if (cdest == 0 && csrc == 0)
		return (0);
	while (i < len)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (cdest);
}
