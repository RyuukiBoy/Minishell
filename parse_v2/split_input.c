/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:18:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/17 09:36:20 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

char	**split_args(char *str)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (count_args(str) + 1));
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			k = i;
			while (str[i] && str[i] != ' ')
				i++;
			args[j++] = ft_substr(str, k, i - k);
		}
	}
	args[j] = NULL;
	return (args);
}
