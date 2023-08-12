/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:16:01 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:01:23 by ybargach         ###   ########.fr       */
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

void	print_env(t_env *head, t_builtin *arr)
{
	t_env	*env;

	free(arr->cmd_ns);
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

t_env	*env_null(t_builtin *arr, t_env **head)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	arr->value = ft_strdup("/Users/ybargach/Desktop/minishell_v2/./minishell");
	add_back(head, "_=", arr->value);
	free(arr->value);
	arr->value = ft_strdup(pwd);
	add_back(head, "PWD=", arr->value);
	free(arr->value);
	arr->value = ft_strdup("1");
	add_back(head, "SHLVL=", arr->value);
	free(arr->value);
	g_exit_value = 0;
	return (*head);
}

t_env	*builtin_env(char **env, t_builtin *arr, t_env **head)
{
	arr->a = 0;
	if (*env == NULL || env == NULL)
		return (env_null(arr, head));
	while (env[arr->a])
	{
		arr->b = 0;
		while (env[arr->a][arr->b])
		{
			if (env[arr->a][arr->b] == '=')
			{
				arr->name = ft_substr(env[arr->a], 0, arr->b + 1);
				arr->value = ft_strdup(env[arr->a] + arr->b + 1);
				add_back(head, arr->name, arr->value);
				free(arr->name);
				free(arr->value);
				break ;
			}
			arr->b++;
		}
		arr->a++;
	}
	g_exit_value = 0;
	return (*head);
}
