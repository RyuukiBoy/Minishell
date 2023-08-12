/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:55:38 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:02:00 by ybargach         ###   ########.fr       */
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
		if ((ft_strcmp("OLDPWD=", env->name) == 0)
			&& ft_strcmp(env->value, pwd) == 0)
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

char	*ft_strdup_quotes(const char *s1)
{
	int		i;
	int		a;
	char	*s2;
	char	*s;

	if (!s1)
		return (NULL);
	s2 = (char *)s1;
	s = (char *)malloc(sizeof(char) * ft_strlen(s2) + 1);
	i = 0;
	a = 0;
	if (!s)
		return (0);
	while (s2[i])
	{
		if (s2[i] == '\"')
			i++;
		if (s2[i] == '\0')
			break ;
		s[a++] = s2[i++];
	}
	s[a] = '\0';
	return (s);
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
				arr->value = ft_strdup_quotes(add + arr->b + 1);
			else
				arr->value = NULL;
			check_add(head, arr);
			if (arr->c == 0)
				add_back(head, arr->name, arr->value);
			free(arr->name);
			free(arr->value);
			break ;
		}
		arr->b++;
	}
}

void	builtin_export(t_env *head, char **add, t_builtin *arr)
{
	t_env	*new_stack;
	t_env	*sort;

	g_exit_value = 0;
	free(arr->cmd_ns);
	new_stack = NULL;
	if (add[1] == NULL)
	{
		sort = sort_export(head, arr);
		print_export(sort);
	}
	else
	{
		arr->ex_b = 0;
		arr->ex_a = check_path(arr, add, &head);
		while (arr->ex_b < arr->add_a - 1)
		{
			if (check_first_char(add[arr->ex_b + 1]) == 1)
				return ;
			if (arr->ex_a[arr->ex_b] == 0)
				builtin_add(&head, arr, add[arr->ex_b + 1]);
			arr->ex_b++;
		}
		free(arr->ex_a);
	}
}
