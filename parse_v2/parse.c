/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:43:15 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/25 13:08:09 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_spaces(char *str)
{
	int		len;
	char	*new;
	char	prev;
	int		i;
	int		j;

	i = 0;
	j = 0;
	prev = '\0';
	len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len * 3 + 1));
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			new[j++] = str[i++];
			new[j++] = str[i++];
			prev = '\0';
			continue ;
		}
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
		{
			if (prev != ' ')
				new[j++] = ' ';
			new[j++] = str[i];
			if (str[i + 1] != ' ')
				new[j++] = ' ';
		}
		else
			new[j++] = str[i];
		prev = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
