/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:38:02 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/15 00:44:50 by oait-bad         ###   ########.fr       */
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

int	check_op(int *arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arr[i])
	{
		if (arr[i] == HEREDOC_SIG && arr[i + 1] != HEREDOC_LIM)
			flag = 1;
		else if (arr[i] == R_IN_SIG && arr[i + 1] != R_IN_FILE)
			flag = 1;
		else if (arr[i] == R_OUT_SIG && arr[i + 1] != R_OUT_FILE)
			flag = 1;
		else if (arr[i] == R_APP_SIG && arr[i + 1] != R_APP_FILE)
			flag = 1;
		i++;
	}
	if (flag)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (0);
	}
	return (1);
}

int	check_all_opers(int *arr)
{
	if (check_pipes(arr) || check_last_pipe(arr) || check_op(arr))
		return (0);
	return (1);
}
