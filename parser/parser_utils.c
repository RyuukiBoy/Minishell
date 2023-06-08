/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:27:19 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/08 11:47:43 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_between_quotes(char *str)
{
	int		single;
	int		doubleq;
	int		i;

	i = ft_strlen(str) - 1;
	single = 0;
	doubleq = 0;
	while (i >= 0)
	{
		if (str[i] == '\'')
			single++;
		if (str[i] == '\"')
			doubleq++;
		i--;
	}
	if (single % 2 == 0 && doubleq % 2 == 0)
		return (0);
	return (1);
}

char	**split_by_pipes(char **input)
{
	char	**pipes;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	pipes = (char **)malloc(sizeof(char *) * (ft_strlen(*input) + 1));
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
		{
			i++;
			while ((*input)[i] && (*input)[i] != '\'' && (*input)[i] != '\"')
				i++;
		}
		if ((*input)[i] == '|')
		{
			pipes[j] = ft_substr(*input, k, i - k);
			j++;
			k = i + 1;
		}
		i++;
	}
	pipes[j] = ft_substr(*input, k, i - k);
	pipes[j + 1] = 0;
	return (pipes);
}

