/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:56:12 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 07:56:54 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expaton_norm(t_builtin *arr, t_env *new_env)
{
	dollar_function(arr, new_env);
	arr->arr_a = -1;
}

void	ft_free_dollar(t_builtin *arr)
{
	free(arr->char_bef);
	free(arr->char_now);
	free(arr->char_aft);
	free(arr->half_line);
	free(arr->now_new);
}

void	ft_free_qoutes(t_builtin *arr)
{
	free(arr->quo_befor);
	free(arr->quo_now);
	free(arr->quo_after);
	free(arr->quo_lin);
}

void	in_quote(t_builtin *arr)
{
	free(arr->quo_bef);
	free(arr->quo_half);
	free(arr->quo_aft);
	free(arr->joi_quo);
	free(arr->quo_new);
}

void	src_env_quo(t_builtin *arr, t_env *new_env)
{
	arr->quo_out = ft_strjoin_simple(arr->quo_half, "=");
	while (new_env)
	{
		if (ft_strcmp(arr->quo_out, new_env->name) == 0)
		{
			if (new_env->value != NULL)
				arr->quo_new = ft_strdup(new_env->value);
			else
				arr->quo_new = ft_strdup("");
			free(arr->quo_out);
			return ;
		}
		new_env = new_env->next;
	}
	arr->quo_new = ft_strdup("");
	free(arr->quo_out);
}
