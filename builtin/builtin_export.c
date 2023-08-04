/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:55:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 11:38:36 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *head)
{
	t_env	*env;

	env = head;
	while (env != NULL)
	{
		printf("declare -x %s", env->name);
		if (env->value != NULL)
			printf("\"%s\"\n", env->value);
		else
			printf("\n");
		env = env->next;
	}
}

t_env	*sort_export(t_env *head, t_builtin *arr)
{
	t_env	*new_node;
	t_env	*tmp;

	if (head == NULL || head->next == NULL)
		return (head);
	new_node = head;
	tmp = NULL;
	while (new_node != NULL)
	{
		tmp = new_node->next;
		while (tmp != NULL)
		{
			if (strcmp(new_node->name, tmp->name) > 0)
				swap_env(new_node, tmp, arr);
			tmp = tmp->next;
		}
		new_node = new_node->next;
	}
	return (head);
}

t_env	*before_sort(t_env *head)
{
	t_env	*new_node;

	if (head == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	new_node->name = (head)->name;
	new_node->value = (head)->value;
	new_node->next = before_sort((head)->next);
	return (new_node);
}

void	builtin_add(t_env **head, t_builtin *arr, char **add)
{
	check_path(arr, add);
	arr->a = 1;
	while (add[arr->a])
	{
		arr->b = 0;
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b] == '=' || add[arr->a][arr->b + 1] == '\0')
			{
				arr->name = ft_substr(add[arr->a], 0, arr->b + 1);
				if (add[arr->a][arr->b] == '=')
					arr->value = ft_strdup(add[arr->a] + arr->b + 1);
				else
					arr->value = NULL;
				arr->d = check_add(head, arr);
				if (arr->d == 0)
					add_back(head, arr->name, arr->value);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
}

void	builtin_export(t_env *head, char **add, t_builtin *arr)
{
	t_env	*new_stack;
	t_env	*sort;
	printf("%s\n", add[0]);
	printf("%s\n", add[1]);

	if (add[1] == NULL)
	{
		new_stack = before_sort(head);
		sort = sort_export(new_stack, arr);
		print_export(sort);
	}
	else
		builtin_add(&head, arr, add);
}
