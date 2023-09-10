/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:06:51 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/09 14:09:33 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_last_qoutes_file(char *cmd, int a)
{
	a++;
	while (cmd[a] != '\'' && cmd[a] != '\0')
	{
		a++;
	}
	return (a);
}

int	check_qoutes_file(char *cmd, int a)
{
	if (cmd[a] == '\"')
		a = check_first_qoutes_file(cmd, a);
	else if (cmd[a] == '\'')
		a = check_last_qoutes_file(cmd, a);
	return (a);
}

int	check_first_qoutes_file(char *cmd, int a)
{
	a++;
	while (cmd[a] != '\"' && cmd[a] != '\0')
		a++;
	return (a);
}
