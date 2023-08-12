/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_multi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:45:11 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:01:37 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_exit_multi(char *add)
{
	printf("minishell: exit: %s: numeric argument required\n", add);
	g_exit_value = 255;
}

void	welcome_to_exit_multi(char *add, t_builtin *arr)
{
	arr->a = 0;
	if (add[arr->a] == '-' || add[arr->a] == '+')
		arr->a++;
	while (add[arr->a])
	{
		if (!(add[arr->a] >= '0' && add[arr->a] <= '9'))
		{
			print_error_exit_multi(add);
			return ;
		}
		arr->a++;
	}
	print_exit_multi(add);
}

void	many_error_exit_multi(void)
{
	printf("minishell: exit: too many aruments\n");
	g_exit_value = 1;
}

void	check_exit_multi(char **add, t_builtin *arr)
{
	arr->a = 0;
	if (add[1][arr->a] == '-' || add[1][arr->a] == '+')
		arr->a++;
	while (add[1][arr->a])
	{
		if (!(add[1][arr->a] >= '0' && add[1][arr->a] <= '9'))
		{
			printf("minishell: exit: %s: numeric argument required\n", add[1]);
			g_exit_value = 255;
			exit(255);
		}
		arr->a++;
	}
	if (add[2] != NULL)
		many_error_exit_multi();
}

void	builtin_exit_multi(char **add, t_builtin *arr)
{
	arr->a = 1;
	g_exit_value = 0;
	if (add[1] == NULL)
		g_exit_value = 0;
	else
	{
		if (ft_strlen_pointer(add) == 2)
			welcome_to_exit_multi(add[1], arr);
		else
			check_exit_multi(add, arr);
	}
}
