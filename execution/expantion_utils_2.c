/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 07:56:22 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 21:49:14 by ybargach         ###   ########.fr       */
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

void	quo_num_exit(t_builtin *arr, int a)
{
	char	*exite;

	arr->quot_s = a;
	arr->quo_bef = ft_substr_simple(arr->quo_now, 0, arr->quot_s);
	arr->quot_e = a + 2;
	arr->quo_aft = alloc_str(arr->quo_now,
			arr->quot_e, ft_strlen_int(arr->quo_now));
	exite = ft_itoa(g_exit_value);
	arr->joi_quo = ft_strjoin_simple(arr->quo_bef, exite);
	free(arr->quo_now);
	arr->quo_now = ft_strjoin_simple(arr->joi_quo, arr->quo_aft);
	free(arr->joi_quo);
	free(arr->quo_bef);
	free(arr->quo_aft);
	free(exite);
}

void	quo_number(t_builtin *arr, int a)
{
	if (arr->quo_now[a + 1] == '?')
		quo_num_exit(arr, a);
	else if (arr->quo_now[a + 1] >= '0'
		&& arr->quo_now[a + 1] <= '9')
	{
		arr->old_lin = ft_strlen_int(arr->quo_now);
		arr->quot_s = a;
		arr->quo_bef = ft_substr_simple(arr->quo_now, 0, arr->quot_s);
		arr->quot_e = a + 2;
		arr->quo_aft = alloc_str(arr->quo_now,
				arr->quot_e, ft_strlen_int(arr->quo_now));
		free(arr->quo_now);
		arr->quo_now = ft_strjoin_simple(arr->quo_bef, arr->quo_aft);
		free(arr->quo_bef);
		free(arr->quo_aft);
	}
}
