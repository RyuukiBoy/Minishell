/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:56:22 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 07:57:00 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	src_env(t_builtin *arr, t_env *new_env)
{
	arr->now_equa = ft_strjoin_simple(arr->char_now, "=");
	while (new_env)
	{
		if (ft_strcmp(arr->now_equa, new_env->name) == 0)
		{
			if (new_env->value != NULL)
				arr->now_new = ft_strdup(new_env->value);
			else
				arr->now_new = ft_strdup("");
			free(arr->now_equa);
			return ;
		}
		new_env = new_env->next;
	}
	arr->now_new = ft_strdup("");
	free(arr->now_equa);
}

int	check_expa(t_builtin *arr)
{
	if (arr->bf_cmd[arr->arr_a][arr->arr_b] == '$'
				&& arr->bf_cmd[arr->arr_a][arr->arr_b + 1] == '\0')
	{
		return (1);
	}
	return (0);
}
