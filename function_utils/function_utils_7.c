/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:06:51 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 09:03:29 by oait-bad         ###   ########.fr       */
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

void	here_norm(t_all all, t_builtin *arr, char *b_limir)
{
	all.fd->infd = here_doc(arr, b_limir);
	return ;
}
