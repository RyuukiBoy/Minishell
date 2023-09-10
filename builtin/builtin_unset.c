/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:09 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/13 01:00:30 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unset(t_builtin *arr, char **add)
{
	if (!((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_' || add[arr->a][arr->b] == '+'))
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_exit_value = 1;
	}
}

void	delet_un(t_env **head, t_env *current, t_env *prev, t_env *tmp)
{
	if (prev == NULL)
		cmp_delete(head, tmp, current);
	else
		cmp_delete_two(current, prev);
}

void	delete_unset(t_env **head, t_builtin *arr)
{
	t_env	*current;
	t_env	*prev;
	t_env	*tmp;

	tmp = NULL;
	prev = NULL;
	current = *head;
	while (current != NULL)
	{
		arr->new_name = ft_strdup_unset(current->name);
		if (ft_strcmp(arr->name, "_") == 0)
		{
			free(arr->new_name);
			return ;
		}
		if (ft_strcmp(arr->name, arr->new_name) == 0)
		{
			delet_un(head, current, prev, tmp);
			free(arr->new_name);
			return ;
		}
		free(arr->new_name);
		prev = current;
		current = current->next;
	}
}

void	builtin_check(t_env **head, t_builtin *arr, char **add)
{
	check_cmd_unset(arr, add);
	arr->a = 1;
	while (add[arr->a])
	{
		if (check_first_char(add[arr->a]) == 1)
			break ;
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b + 1] == '\0')
			{
				arr->name = ft_substr(add[arr->a], 0, arr->b + 1);
				delete_unset(head, arr);
				free(arr->name);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
}

void	builtin_unset(t_env **head, t_builtin *arr, char **add)
{
	free(arr->cmd_ns);
	g_exit_value = 0;
	if (add[1] != NULL)
		builtin_check(head, arr, add);
	else
		return ;
}
