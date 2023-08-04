/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:16:08 by ybargach          #+#    #+#             */
/*   Updated: 2023/07/31 13:23:25 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_execve(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (0);
	d = (ft_strlen(s1) + ft_strlen(s2) + 2);
	a = 0;
	b = 0;
	p = malloc(d * sizeof(char));
	if (!p)
		return (0);
	while (s1[b] && d - 1 > a)
	{
		p[a] = s1[b];
		a++;
		b++;
	}
	p[a++] = '/';
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}
