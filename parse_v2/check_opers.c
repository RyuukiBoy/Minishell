/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:38:02 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 11:09:11 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			return (0);
		}
		else if (line[0] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_last_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '|')
	{
		printf("minishell: syntax error near unexpected end of file\n");
		return (0);
	}
	return (1);
}

int	only_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<')
			return (0);
		i++;
	}
	return (1);
}

int	norm_redirections_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '>')
		{
			printf("minishell: syntax error near unexpected token `<>'\n");
			return (0);
		}
		else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		else if (only_redirection(str))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		i++;
	}
	return (1);
}
