/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:55:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/05 18:11:04 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *head)
{
	t_env	*env;
	char	pwd[1024];

	if (head == NULL)
		return ;
	env = head;
	getcwd(pwd, 1024);
	while (env != NULL)
	{
		if ((ft_strcmp("OLDPWD=", env->name) == 0) && ft_strcmp(env->value, pwd) == 0)
			printf("declare -x OLDPWD\n");
		else
		{
			printf("declare -x %s", env->name);
			if (env->value != NULL)
				printf("\"%s\"\n", env->value);
			else
				printf("\n");
		}
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
			if (ft_strcmp(new_node->name, tmp->name) > 0)
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

void	builtin_add(t_env **head, t_builtin *arr, char *add)
{
	arr->b = 0;
	while (add[arr->b])
	{
		if (add[arr->b] == '=' || add[arr->b + 1] == '\0')
		{
			arr->name = ft_substr(add, 0, arr->b + 1);
			if (add[arr->b] == '=')
				arr->value = ft_strdup(add + arr->b + 1);
			else
				arr->value = NULL;
			arr->d = check_add(head, arr);
			if (arr->d == 0)
				add_back(head, arr->name, arr->value);
			break ;
		}
		arr->b++;
	}
}

void	builtin_export(t_env *head, char **add, t_builtin *arr)
{
	int		*a;
	int		b;
	t_env	*new_stack;
	t_env	*sort;

	if (add[1] == NULL)
	{
		new_stack = before_sort(head);
		sort = sort_export(new_stack, arr);
		print_export(sort);
	}
	else
	{
		b = 0;
		a = check_path(arr, add, &head);
		while (b < arr->add_a - 1)
		{
			if (a[b] == 0)
				builtin_add(&head, arr, add[b + 1]);
			b++;
		}
	}
}
