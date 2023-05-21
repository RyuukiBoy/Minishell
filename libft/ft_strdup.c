/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:48:50 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:53:24 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;
	char	*s;

	s2 = (char *)s1;
	s = (char *)malloc(sizeof(char) * ft_strlen(s2) + 1);
	i = 0;
	if (!s)
		return (0);
	while (i < ft_strlen(s2))
	{
		s[i] = s2[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
