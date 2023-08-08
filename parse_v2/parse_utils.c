/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:55:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 15:00:16 by oait-bad         ###   ########.fr       */
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

void	print_it(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
}

void	free_exp(t_exp *exp)
{
	free(exp->key);
	free(exp->tmp);
	free(exp->before);
	free(exp->after);
}

int	is_inside_squotes(char *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (str[j] == '\'')
			return (1);
		j++;
	}
	return (0);
}
