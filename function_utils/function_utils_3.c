/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:21:40 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/02 15:15:07 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_av_ac(int ac, char **av)
{
	if (ac != 1)
	{
		printf("error args %s\n", *av);
		exit(1);
	}
}

int	ft_strlen_double(char *cmd, t_builtin *arr)
{
	arr->str_a = 0;
	while (cmd[arr->str_a])
	{
		if (cmd[arr->str_a] != '<' || cmd[arr->str_a] != '>' || cmd[arr->str_a] != ' ' || cmd[arr->str_a] != '\t')
			return 2;
		arr->str_a++;
	}
	return (1);
}
