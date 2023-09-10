/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:31:59 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 21:51:18 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with(t_builtin *arr)
{
	char	*exit;

	arr->old_lin = ft_strlen_int(arr->bf_cmd[arr->arr_a]);
	arr->expa_b = arr->arr_b;
	arr->char_bef = ft_substr_simple(arr->bf_cmd[arr->arr_a], 0, arr->expa_b);
	arr->arr_b += 2;
	arr->expa_m = arr->arr_b;
	arr->char_aft = alloc_str(arr->bf_cmd[arr->arr_a],
			arr->expa_m, arr->old_lin);
	exit = ft_itoa(g_exit_value);
	arr->half_line = ft_strjoin_simple(arr->char_bef, exit);
	free(arr->bf_cmd[arr->arr_a]);
	arr->bf_cmd[arr->arr_a] = ft_strjoin_simple(arr->half_line, arr->char_aft);
	free(arr->char_bef);
	free(arr->char_aft);
	free(arr->half_line);
	free(exit);
}

void	exit_values(t_builtin *arr)
{
	if (arr->bf_cmd[arr->arr_a][arr->arr_b + 1] == '?')
		exit_with(arr);
	else if (arr->bf_cmd[arr->arr_a][arr->arr_b + 1] >= '0'
		&& arr->bf_cmd[arr->arr_a][arr->arr_b + 1] <= '9')
	{
		arr->old_lin = ft_strlen_int(arr->bf_cmd[arr->arr_a]);
		arr->expa_b = arr->arr_b;
		arr->char_bef = ft_substr_simple(arr->bf_cmd[arr->arr_a],
				0, arr->expa_b);
		arr->arr_b += 2;
		arr->char_now = alloc_str(arr->bf_cmd[arr->arr_a],
				arr->arr_b, arr->old_lin);
		free(arr->bf_cmd[arr->arr_a]);
		arr->bf_cmd[arr->arr_a] = ft_strjoin_simple(arr->char_bef,
				arr->char_now);
		free(arr->char_now);
		free(arr->char_bef);
	}
}

char	*alloc_str(char *str, int start, int end)
{
	char	*p;
	int		a;

	a = 0;
	if (str == NULL)
		return (NULL);
	p = malloc(end - start + 2);
	if (!p)
		return (NULL);
	while (start <= end)
	{
		p[a] = str[start];
		a++;
		start++;
	}
	p[a] = '\0';
	return (p);
}

void	check_is_ex_nor(t_builtin *arr, t_env *new_env)
{
	arr->quo_bef = ft_substr_simple(arr->quo_now, 0, arr->quot_s - 1);
	arr->quo_half = alloc_str(arr->quo_now, arr->quot_s, arr->quot_e);
	src_env_quo(arr, new_env);
	arr->quo_aft = alloc_str(arr->quo_now,
			arr->quot_e + 1, ft_strlen_int(arr->quo_now));
	arr->joi_quo = ft_strjoin_simple(arr->quo_bef, arr->quo_new);
	free(arr->quo_now);
	arr->quo_now = ft_strjoin_simple(arr->joi_quo, arr->quo_aft);
}

void	check_is_expa(t_builtin *arr, t_env *new_env)
{
	int	a;

	a = 0;
	while (arr->quo_now[a] != '\0')
	{
		if (arr->quo_now[a] == '$')
		{
			if (arr->quo_now[a + 1] == '?'
				|| (arr->quo_now[a + 1] >= '0' && arr->quo_now[a + 1] <= '9'))
				quo_number(arr, a);
			else
			{
				a++;
				arr->quot_s = a;
				while (ft_isalnum(arr->quo_now[a]))
					a++;
				arr->quot_e = a - 1;
				check_is_ex_nor(arr, new_env);
				in_quote(arr);
			}
			check_is_expa(arr, new_env);
			a = 0;
		}
		a++;
	}
}
