/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:44:56 by oait-bad          #+#    #+#             */
/*   Updated: 2022/12/21 13:53:43 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*nstr;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	nstr = (char *)malloc(sizeof(char) * len);
	if (!nstr)
		return (0);
	ft_strlcpy(nstr, s1, len);
	ft_strlcat(nstr, s2, len);
	nstr[len - 1] = '\0';
	return (nstr);
}
