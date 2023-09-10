/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:13:11 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 15:54:47 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_pointer(char **add)
{
	int	a;

	a = 0;
	while (add[a])
		a++;
	return (a);
}

void	welcome_to_exit(char *add, t_builtin *arr)
{
	arr->a = 0;
	if (add[arr->a] == '-' || add[arr->a] == '+')
		arr->a++;
	while (add[arr->a])
	{
		if (!(add[arr->a] >= '0' && add[arr->a] <= '9'))
		{
			print_error_exit(add);
			return ;
		}
		arr->a++;
	}
	print_exit(add);
}

void	many_error_exit(void)
{
	printf("exit\n");
	printf("minishell: exit: too many aruments\n");
	g_exit_value = 1;
}

void	check_exit(char **add, t_builtin *arr)
{
	arr->a = 0;
	if (add[1][arr->a] == '-' || add[1][arr->a] == '+')
		arr->a++;
	while (add[1][arr->a])
	{
		if (!(add[1][arr->a] >= '0' && add[1][arr->a] <= '9'))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", add[1]);
			g_exit_value = 255;
		}
		arr->a++;
	}
	many_error_exit();
}

void	builtin_exit(char **add, t_builtin *arr)
{
	free(arr->cmd_ns);
	arr->a = 1;
	if (add[1] == NULL)
	{
		printf("exit\n");
		g_exit_value = 0;
		exit (g_exit_value);
	}
	else
	{
		if (ft_strlen_pointer(add) == 2)
			welcome_to_exit(add[1], arr);
		else
			check_exit(add, arr);
	}
}
