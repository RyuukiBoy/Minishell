/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:57:19 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/10 06:59:08 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_send_red(char *str, t_builtin *arr)
{
	char	*cmd;

	if (str[arr->str_b] == ' ' || str[arr->str_b] == '\t')
		arr->str_b++;
	arr->start_red = arr->str_b;
	while (str[arr->str_b])
	{
		if (str[arr->str_b + 1] == '\0')
			break ;
		if (str[arr->str_b] == '\"' || str[arr->str_b] == '\'')
			arr->str_b = check_qoutes_red(str, arr);
		if (!(str[arr->str_b] >= 33 && str[arr->str_b] <= 126))
			break ;
		arr->str_b++;
	}
	while (str[arr->str_b] == '\t' || str[arr->str_b] == ' ')
		arr->str_b--;
	cmd = ft_substr_simple(str, arr->start_red, arr->str_b);
	return (cmd);
}

int	check_opera_red(char *cmd, t_builtin *arr)
{
	if (cmd[arr->str_b] >= 42 && cmd[arr->str_b] <= 45)
		return (1);
	else if (cmd[arr->str_b] >= 48 && cmd[arr->str_b] <= 58)
		return (1);
	else if (cmd[arr->str_b] >= 63 && cmd[arr->str_b] <= 91)
		return (1);
	else if (cmd[arr->str_b] >= 93 && cmd[arr->str_b] <= 95)
		return (1);
	else if (cmd[arr->str_b] >= 97 && cmd[arr->str_b] <= 123)
		return (1);
	else if (cmd[arr->str_b] == 33 || cmd[arr->str_b] == 61
		|| cmd[arr->str_b] == 125 || cmd[arr->str_b] == '\0')
		return (1);
	return (0);
}

int	check_opera(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b] >= 42 && cmd[arr->move_b] <= 45)
		return (1);
	else if (cmd[arr->move_b] >= 48 && cmd[arr->move_b] <= 58)
		return (1);
	else if (cmd[arr->move_b] >= 63 && cmd[arr->move_b] <= 91)
		return (1);
	else if (cmd[arr->move_b] >= 93 && cmd[arr->move_b] <= 95)
		return (1);
	else if (cmd[arr->move_b] >= 97 && cmd[arr->move_b] <= 123)
		return (1);
	else if (cmd[arr->move_b] == 33 || cmd[arr->move_b] == 61
		|| cmd[arr->move_b] == 125 || cmd[arr->move_b] == '\0')
		return (1);
	return (0);
}

int	check_opera_quotes(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b - 1] >= 42 && cmd[arr->move_b - 1] <= 45)
		return (1);
	else if (cmd[arr->move_b - 1] >= 48 && cmd[arr->move_b - 1] <= 58)
		return (1);
	else if (cmd[arr->move_b - 1] >= 63 && cmd[arr->move_b - 1] <= 91)
		return (1);
	else if (cmd[arr->move_b - 1] >= 93 && cmd[arr->move_b - 1] <= 95)
		return (1);
	else if (cmd[arr->move_b - 1] >= 97 && cmd[arr->move_b - 1] <= 123)
		return (1);
	else if (cmd[arr->move_b - 1] == 33 || cmd[arr->move_b - 1] == 61
		|| cmd[arr->move_b - 1] == 125 || cmd[arr->move_b] == '\0')
		return (1);
	return (0);
}

int	check_opera_string(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b] >= 42 && cmd[arr->move_b] <= 45)
		return (1);
	else if (cmd[arr->move_b] >= 48 && cmd[arr->move_b] <= 58)
		return (1);
	else if (cmd[arr->move_b] >= 63 && cmd[arr->move_b] <= 91)
		return (1);
	else if (cmd[arr->move_b] >= 93 && cmd[arr->move_b] <= 95)
		return (1);
	else if (cmd[arr->move_b] >= 97 && cmd[arr->move_b] <= 123)
		return (1);
	else if (cmd[arr->move_b] == 33 || cmd[arr->move_b] == 61
		|| cmd[arr->move_b] == 125 || cmd[arr->move_b + 1] == '\0')
		return (1);
	return (0);
}
