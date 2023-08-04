/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/11 14:37:59 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_first_char(t_builtin *arr, char **add)
{
	if (add[arr->a][0] == '\\')
		exit(0);
	if (!((add[arr->a][0] >= 'a' && add[arr->a][0] <= 'z')
		|| (add[arr->a][0] >= 'A' && add[arr->a][0] <= 'Z')
		|| add[arr->a][0] == '_'))
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		exit(1);
	}
}

void	swap_env(t_env *new_node, t_env *tmp, t_builtin *arr)
{
	arr->name = new_node->name;
	new_node->name = tmp->name;
	tmp->name = arr->name;
	arr->value = new_node->value;
	new_node->value = tmp->value;
	tmp->value = arr->value;
}

void	check_char(t_builtin *arr, char **add)
{
	if ((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_' || add[arr->a][arr->b] == '+')
	{
		if ((add[arr->a][arr->b] == '+' && add[arr->a][arr->b + 1] != '='))
		{
			ft_putstr_fd(add[arr->a], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			exit(1);
		}
	}
	else
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		exit(1);
	}
}
