/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:43:15 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/09 07:08:11 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_last_redir(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0 && (line[i - 1] == '<' || line[i - 1] == '>'))
	{
		printf("minishell: syntax error near unexpected `newline'\n");
		return (0);
	}
	return (1);
}

int	check_redirections(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		{
			printf("minishell: syntax error near unexpected token '>'\n");
			return (0);
		}
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			printf("minishell: syntax error near unexpected token '<'\n");
			return (0);
		}
		else if (str[i] == '>' && str[i + 1] == '<')
		{
			printf("minishell: syntax error near unexpected token `><'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_redirections_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t')
			{
				i++;
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (str[i] == '>' || str[i] == '<' || str[i] == '|')
				{
					print_it(str[i]);
					return (0);
				}
				i--;
			}
		}
		i++;
	}
	return (1);
}

int	check_pipes_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t')
			{
				i++;
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if (str[i] == '|')
				{
					print_it(str[i]);
					return (0);
				}
				i--;
			}
		}
		i++;
	}
	return (1);
}

int	parse(char *line)
{
	if (!check_pipes(line) || !check_last_redir(line) || !check_last_pipe(line))
		return (0);
	else if (!check_redirections(line) || !check_redirections_2(line)
		|| !check_pipes_2(line))
		return (0);
	else if (!norm_redirections_check(line) || !check_quotes(line))
		return (0);
	return (1);
}
