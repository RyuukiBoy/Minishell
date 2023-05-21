/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:55:29 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:52:26 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t			i;
	unsigned char	*ts1;
	unsigned char	*ts2;

	i = 0;
	ts1 = (unsigned char *) s1;
	ts2 = (unsigned char *) s2;
	while (i < len)
	{
		if (ts1[i] - ts2[i] != 0)
		{
			return (ts1[i] - ts2[i]);
		}
		i++;
	}
	return (0);
}
