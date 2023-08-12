/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:14:14 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:57:30 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	double_function_norm(t_builtin *arr, t_env *new_env)
{
	if (arr->bf_cmd[arr->arr_a][arr->quot_st] != '\"')
		arr->quo_befor = ft_substr_simple(arr->bf_cmd[arr->arr_a], 0,
				arr->quot_st);
	else
		arr->quo_befor = ft_substr_simple(arr->bf_cmd[arr->arr_a], 1,
				arr->quot_st);
	arr->quo_now = alloc_str(arr->bf_cmd[arr->arr_a], arr->quot_b,
			arr->quot_en);
	check_is_expa(arr, new_env);
	arr->quo_after = ft_substr_simple(arr->bf_cmd[arr->arr_a],
			arr->quot_a, ft_strlen(arr->bf_cmd[arr->arr_a]));
	arr->quo_lin = ft_strjoin_simple(arr->quo_befor, arr->quo_now);
	arr->arr_b = ft_strlen_int(arr->quo_lin);
}

void	double_function(t_builtin *arr, t_env *new_env)
{
	arr->quot_st = arr->arr_b;
	arr->quot_b = arr->arr_b;
	arr->arr_b++;
	while (arr->bf_cmd[arr->arr_a][arr->arr_b] != '\"')
		arr->arr_b++;
	arr->quot_en = arr->arr_b;
	arr->arr_b++;
	arr->quot_a = arr->arr_b;
	double_function_norm(arr, new_env);
	free(arr->bf_cmd[arr->arr_a]);
	arr->bf_cmd[arr->arr_a] = ft_strjoin_simple(arr->quo_lin, arr->quo_after);
	ft_free_qoutes(arr);
}

void	dollar_function(t_builtin *arr, t_env *new_env)
{
	if (arr->bf_cmd[arr->arr_a][arr->arr_b + 1] == '?'
		|| (arr->bf_cmd[arr->arr_a][arr->arr_b + 1] >= '0'
		&& arr->bf_cmd[arr->arr_a][arr->arr_b + 1] <= '9'))
	{
		exit_values(arr);
		return ;
	}
	arr->old_lin = ft_strlen_int(arr->bf_cmd[arr->arr_a]);
	arr->expa_b = arr->arr_b;
	arr->arr_b++;
	arr->expa_e = arr->arr_b;
	while (ft_isalnum(arr->bf_cmd[arr->arr_a][arr->arr_b]))
		arr->arr_b++;
	arr->expa_m = arr->arr_b;
	arr->expa_af = arr->arr_b;
	arr->char_bef = ft_substr_simple(arr->bf_cmd[arr->arr_a], 0, arr->expa_b);
	arr->char_now = alloc_str(arr->bf_cmd[arr->arr_a],
			arr->expa_e, arr->expa_m - 1);
	src_env(arr, new_env);
	arr->char_aft = alloc_str(arr->bf_cmd[arr->arr_a],
			arr->expa_m, arr->old_lin);
	free(arr->bf_cmd[arr->arr_a]);
	arr->half_line = ft_strjoin_simple(arr->char_bef, arr->now_new);
	arr->bf_cmd[arr->arr_a] = ft_strjoin_simple(arr->half_line, arr->char_aft);
	ft_free_dollar(arr);
}

void	expation(t_builtin *arr, t_env *new_env)
{
	arr->arr_a = 0;
	while (arr->bf_cmd[arr->arr_a])
	{
		arr->arr_b = 0;
		while (arr->bf_cmd[arr->arr_a][arr->arr_b])
		{
			if (check_expa(arr) == 1)
				break ;
			if (arr->bf_cmd[arr->arr_a][arr->arr_b] == '$')
			{
				expaton_norm(arr, new_env);
				break ;
			}
			else if (arr->bf_cmd[arr->arr_a][arr->arr_b] == '\"')
			{
				double_function(arr, new_env);
				if (arr->bf_cmd[arr->arr_a][arr->arr_b + 1] != '\0')
					break ;
			}
			else if (arr->bf_cmd[arr->arr_a][arr->arr_b] == '\'')
				single_function(arr);
			arr->arr_b++;
		}
		arr->arr_a++;
	}
}
