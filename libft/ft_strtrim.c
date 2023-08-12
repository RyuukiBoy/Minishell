/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:16:41 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/03 16:58:19 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_set(const char *str, char tofind)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == tofind)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	if (!set || !s1)
		return (0);
	start = 0;
	while (s1[start] && my_set(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && my_set(set, s1[end - 1]))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

// static int	first(char const *s1, char const *s2)
// {
// 	int	a;
// 	int	b;

// 	a = 0;
// 	b = 0;
// 	while (s1[a] && s2[b])
// 	{
// 		if (s1[a] == s2[b])
// 		{
// 			b = 0;
// 			a++;
// 		}
// 		else if (s1[a] != s2[b])
// 			b++;
// 	}
// 	return (a);
// }

// // static int	last(char const *s1, char const *s2)
// // {
// // 	int	a;
// // 	int	b;

// // 	if (s1 == NULL || s2 == NULL)
// // 		return (0);
// // 	a = (int)ft_strlen(s1) - 1;
// // 	b = 0;
// // 	if (a < 0)
// // 		return (0);
// // 	while (s1[a] && s2[b])
// // 	{
// // 		if (s1[a] == s2[b])
// // 		{
// // 			b = 0;
// // 			a--;
// // 		}
// // 		else if (s1[a] != s2[b])
// // 			b++;
// // 	}
// // 	return (a);
// // }

// static int last(char const *s1, char const *s2)
// {
//     if (s1 == NULL || s2 == NULL)
//         return -1;

//     int a = (int)ft_strlen(s1) - 1;
//     int b;

//     if (a < 0)
//         return -1; // s1 is an empty string. Return -1 for no match.

//     while (s1[a])
//     {
//         b = 0;
//         while (s2[b])
//         {
//             if (s1[a] == s2[b])
//                 return a; // Return the index of the last match.
//             b++;
//         }
//         a--;
//     }

//     return -1; // No match found.
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	int		a;
// 	int		b;
// 	int		c;
// 	int		size;
// 	char	*p;

// 	if (!s1 || !set)
// 		return (0);
// 	a = first(s1, set);
// 	b = last(s1, set);
// 	c = 0;
// 	if (a == (int)ft_strlen(s1))
// 		return (ft_strdup(""));
// 	else
// 		size = b - a + 1;
// 	p = malloc((size + 1) * sizeof(char));
// 	if (!p)
// 		return (0);
// 	while (a <= b)
// 		p[c++] = s1[a++];
// 	p[c] = '\0';
// 	return (p);
// }
