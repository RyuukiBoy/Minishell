/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:01 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 13:39:13 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
}

t_env	*last_node(t_env **env)
{
	t_env	*lastnode;

	lastnode = *env;
	while (lastnode->next != NULL)
		lastnode = lastnode->next;
	return (lastnode);
}

void	add_back(t_env **head, char *name, char *value)
{
	t_env	*newnode;
	t_env	*lastnode;

	if ((*head) == NULL)
		*head = add_env(name, value);
	else
	{
		newnode = add_env(name, value);
		lastnode = last_node(head);
		lastnode->next = newnode;
	}
}

void	print_env(t_env *head)
{
	t_env	*env;

	env = head;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			printf("%s", env->name);
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}

t_env	*builtin_env(char **env, t_builtin *arr, t_env *head)
{
	if (*env == NULL)
	{	
		arr->a = 0;
		while (env[arr->a])
		{
		dprintf(2, "here\n");
			if (ft_strncmp("PATH", env[arr->a], 4) == 0)
			{
				arr->b = 0;
				while (env[arr->a][arr->b])
				{
					dprintf(2, "here\n");
					if (env[arr->a][arr->b] == '=')
					{
						dprintf(2, "here\n");
						arr->name = ft_substr(env[arr->a], 0, arr->b + 1);
						arr->value = ft_strdup(env[arr->a] + arr->b + 1);
						add_back(&head, arr->name, arr->value);
						break ;
					}
					arr->b++;
				}
			}
			arr->a++;
		}
		return (head);
	}
	arr->a = 0;
	while (env[arr->a])
	{
		arr->b = 0;
		while (env[arr->a][arr->b])
		{
			if (env[arr->a][arr->b] == '=')
			{
				arr->name = ft_substr(env[arr->a], 0, arr->b + 1);
				arr->value = ft_strdup(env[arr->a] + arr->b + 1);
				add_back(&head, arr->name, arr->value);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
	return (head);
}
