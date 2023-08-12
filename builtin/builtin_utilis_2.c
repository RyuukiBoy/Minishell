/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:02:11 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_add_equal(t_env **head, t_builtin *arr)
{
	t_env	*new_node;

	arr->c = 0;
	new_node = *head;
	arr->line = ft_strdup_unset(arr->name);
	while (new_node != NULL)
	{
		arr->new_name = ft_strdup_unset(new_node->name);
		if (ft_strcmp(arr->new_name, arr->line) == 0)
		{
			if (arr->value != NULL)
			{
				arr->new_value = ft_strdup(arr->value);
				free(arr->value);
				arr->value = ft_strjoin_equal(new_node->value, arr->new_value);
				free(arr->new_value);
			}
			arr->c = 1;
		}
		free(arr->new_name);
		new_node = new_node->next;
	}
	free(arr->line);
	return (arr->c);
}

void	change_node(t_env **head, char *name, char *value)
{
	t_env	*new_node;

	new_node = *head;
	while (new_node)
	{
		if (ft_strcmp(new_node->name, name) == 0)
		{
			free(new_node->value);
			new_node->value = ft_strdup(value);
		}
		new_node = new_node->next;
	}
}

void	export_equal(t_builtin *arr, char *add, t_env **head)
{
	arr->b = 0;
	while (add[arr->b])
	{
		if (add[arr->b] == '+')
		{
			arr->name = ft_substr_equal(add, 0, arr->b + 1);
			arr->b = arr->b + 1;
			arr->value = ft_strdup(add + arr->b + 1);
			arr->d = check_add_equal(head, arr);
			if (arr->d == 0)
				add_back(head, arr->name, arr->value);
			else if (arr->d == 1)
				change_node(head, arr->name, arr->value);
			free(arr->value);
			free(arr->name);
			break ;
		}
		arr->b++;
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

int	check_first_char(char*add)
{
	if (!((add[0] >= 'a' && add[0] <= 'z')
			|| (add[0] >= 'A' && add[0] <= 'Z')
			|| add[0] == '_'))
	{
		ft_putstr_fd(add, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_exit_value = 1;
		return (1);
	}
	return (0);
}
