/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:55:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/03 15:18:25 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_spaces(char *str)
{
	int		len;
	char	*new_str;
	char	prev;
	int		i;
	int		j;

	i = 0;
	j = 0;
	prev = '\0';
	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (len * 3 + 1));
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
			prev = ' ';
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
		{
			if (prev != ' ')
				new_str[j++] = ' ';
			new_str[j++] = str[i++];
			if (str[i] != ' ')
				new_str[j++] = ' ';
			prev = ' ';
		}
		else
		{
			new_str[j++] = str[i++];
			prev = str[i - 1];
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
