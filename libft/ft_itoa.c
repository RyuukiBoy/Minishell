/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:16:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/12 10:38:06 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

static int	ft_nbrpow(int nbr)
{
	int	pow;

	pow = 1;
	while (nbr > 9 || nbr < -9)
	{
		nbr /= 10;
		pow++;
	}
	return (pow);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		neg;

	neg = n < 0;
	len = ft_nbrpow(n) + neg;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len] = ft_abs(n % 10) + '0';
		n /= 10;
		len--;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
