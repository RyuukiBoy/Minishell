/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/09 13:37:55 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_qoutes(char *cmd, t_builtin *arr)
{
	arr->move_b++;
	while (cmd[arr->move_b] != '\"' && cmd[arr->move_b] != '\0')
		arr->move_b++;
	return (arr->move_b);
}

int	check_last_qoutes(char *cmd, t_builtin *arr)
{
	arr->move_b++;
	while (cmd[arr->move_b] != '\'' && cmd[arr->move_b] != '\0')
		arr->move_b++;
	return (arr->move_b);
}

int	check_first_qoutes_red(char *cmd, t_builtin *arr)
{
	arr->str_b++;
	while (cmd[arr->str_b] != '\"' && cmd[arr->str_b] != '\0')
		arr->str_b++;
	return (arr->str_b);
}

int	check_last_qoutes_red(char *cmd, t_builtin *arr)
{
	arr->str_b++;
	while (cmd[arr->str_b] != '\'' && cmd[arr->str_b] != '\0')
		arr->str_b++;
	return (arr->str_b);
}

int	check_qoutes_red(char *cmd, t_builtin *arr)
{
	if (cmd[arr->str_b] == '\"')
		arr->str_b = check_first_qoutes_red(cmd, arr);
	else if (cmd[arr->str_b] == '\'')
		arr->str_b = check_last_qoutes_red(cmd, arr);
	return (arr->str_b);
}
