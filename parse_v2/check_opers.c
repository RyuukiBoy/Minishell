/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:38:02 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/03 11:06:02 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int	check_pipes(int *arr)
//{
//	int	i;

//	i = 0;
//	while (arr[i])
//	{
//		if (arr[i] == PIPE && arr[i + 1] == PIPE)
//		{
//			printf("minishell: syntax error near unexpected token `||'\n");
//			return (0);
//		}
//		else if (arr[0] == PIPE)
//		{
//			printf("minishell: syntax error near unexpected token `|'\n");
//			return (0);
//		}
//		i++;
//	}
//	return (1);
//}

//int	check_last_pipe(int *arr)
//{
//	int	i;

//	i = 0;
//	while (arr[i])
//		i++;
//	if (arr[i - 1] && arr[i - 1] == PIPE)
//	{
//		printf("minishell: syntax error near unexpected end of file\n");
//		return (0);
//	}
//	return (1);
//}

//int	check_redirections(char *str)
//{
//	int	i;

//	i = 0;
//	while (str[i])
//	{
//		i = skip_whitespaces(str, i);
//		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
//		{
//			printf("minishell: syntax error near unexpected token '>'\n");
//			return (0);
//		}
//		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
//		{
//			printf("minishell: syntax error near unexpected token '<'\n");
//			return (0);
//		}
//		else if (str[i] == '>' && str[i + 1] == '<')
//		{
//			printf("minishell: syntax error near unexpected token `><'\n");
//			return (0);
//		}
//		else if (str[i] == '<' && str[i + 1] == '>')
//		{
//			printf("minishell: syntax error near unexpected token `<>'\n");
//			return (0);
//		}
//		else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '|')
//		{
//			printf("minishell: syntax error near unexpected token `|'\n");
//			return (0);
//		}
//		i++;
//	}
//	return (1);
//}
