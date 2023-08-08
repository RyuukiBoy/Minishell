/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_multi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:45:11 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 15:31:08 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_exit_multi(char *add)
{
	printf("minishell: exit: %s: numeric argument required\n", add);
	//exit_value = 255;
}

void	print_exit_multi(char *add)
{
	int	a;
	int	b;

	a = ft_atoi(add);
	if (a >= 0)
	{
		b = a % 256;
		//exit_value = b;
	}
	else
	{
		b = (a % 256 + 256) % 256;
		//exit_value = b;
	}
}

void	welcome_to_exit_multi(char *add, t_builtin *arr)
{
	arr->a = 0;
	if (add[arr->a] == '-' || add[arr->a] == '+')
		arr->a++;
	while (add[arr->a])
	{
		if (!(add[arr->a] >= '0' && add[arr->a] <= '9'))
			print_error_exit_multi(add);
		arr->a++;
	}
	print_exit_multi(add);
}

void	many_error_exit_multi(char **add)
{
	printf("minishell: exit: too many aruments\n");
	//exit_value = 1;
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
			//exit_value = 255;
		}
		arr->a++;
	}
	many_error_exit_multi(add);
}

void	builtin_exit_multi(char **add, t_builtin *arr)
{
	arr->a = 1;
	//if (add[1] == NULL)
	//	exit_value = 0;
	//else
	//{
		if (ft_strlen_pointer(add) == 2)
			welcome_to_exit_multi(add[1], arr);
		else
			check_exit_multi(add, arr);
	//}
}
