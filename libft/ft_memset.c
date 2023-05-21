/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:22:49 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:52:45 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *a, int n, size_t len)

{	
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)a;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)n;
		i++;
	}
	return (p);
}
