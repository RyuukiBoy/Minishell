/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:27:19 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/09 20:24:17 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if ((*input)[i] == '|' && ((*input)[i + 2] == '|' || (*input)[i + 1] == '\0'))
		{
			printf("syntax error near unexpected token `||'\n");
			return (0);
		}
		i++;
	}
	pipes[j] = ft_substr(*input, k, i - k);
	pipes[j + 1] = 0;
	return (pipes);
}
