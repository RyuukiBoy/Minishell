/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:09 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 13:36:59 by ybargach         ###   ########.fr       */
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
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *head;
	while (current != NULL) 
	{
		arr->new_name = ft_strdup_unset(current->name);
		if (ft_strcmp(arr->name, arr->new_name) == 0) 
		{
			if (prev == NULL)
			{
				t_env *tmp;
				tmp = current->next;
				*head = tmp;
				free(current->name);
				free(current->value);
				free(current);
				current = tmp;
			} 
			else
			{
				prev->next = current->next;
				free(current->name);
				free(current->value);
				free(current);
			}
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
	if (add[1] != NULL)
		builtin_check(head, arr, add);
	else
		return ;
}
