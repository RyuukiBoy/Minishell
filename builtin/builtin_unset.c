/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:09 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/14 11:00:39 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unset(t_builtin *arr, char **add)
{
	if (!((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_'))
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		exit(1);
	}
}

void	check_cmd_unset(t_builtin *arr, char **add)
{
	arr->a = 0;
	while (add[arr->a])
	{
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			check_unset(arr, add);
			arr->b++;
		}
		arr->a++;
	}
}

void	delete_unset(t_env **head, t_builtin *arr)
{
	t_env	*new_node;
	t_env	*delete_node;

	new_node = *head;
	delete_node = NULL;
	arr->new_name = ft_strdup_unset(new_node->name);
	while (new_node != NULL && strcmp(arr->new_name, arr->name) != 0)
	{
		free(arr->new_name);
		delete_node = new_node;
		new_node = new_node->next;
		arr->new_name = ft_strdup_unset(new_node->name);
	}
	free(arr->new_name);
	if (new_node == NULL)
		return ;
	if (delete_node == NULL)
		*head = new_node->next;
	else
		delete_node->next = new_node->next;
	free(new_node->name);
	free(new_node->value);
	free(new_node);
}

void	builtin_check(t_env **head, t_builtin *arr, char **add)
{
	check_cmd_unset(arr, add);
	arr->a = 0;
	while (add[arr->a])
	{
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b + 1] == '\0')
			{
				arr->name = ft_substr(add[arr->a], 0, arr->b + 1);
				delete_unset(head, arr);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
}

void	builtin_unset(t_env *head, t_builtin *arr, char **add)
{
	if (*add != NULL)
		builtin_check(&head, arr, add);
}
