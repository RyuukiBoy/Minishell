/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:38:02 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/26 18:03:08 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(int *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == PIPE && arr[i + 1] == PIPE)
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			return (0);
		}
		else if (arr[0] == PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_last_pipe(int *arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (arr[i - 1] && arr[i - 1] == PIPE)
	{
		printf("minishell: syntax error near unexpected end of file\n");
		return (0);
	}
	return (1);
}

int	check_op(char *arr)
{
	int	i;

	i = 0;
	if ((arr[i] == '>' || arr[i] == '<')
		|| (arr[i + 1] == ' ' || arr[i + 1] == '\t'))
	{
		i = skip_whitespaces(arr + 1, i);
		if (arr[i] == '>' || arr[i] == '<' || arr[i] == '|')
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_all_opers(int *arr)
{
	if (check_pipes(arr) == 1 || check_last_pipe(arr) == 0)
		return (0);
	return (1);
}
