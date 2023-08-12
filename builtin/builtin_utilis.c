/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:07:11 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/11 23:03:48 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*last_node(t_env **env)
{
	t_env	*lastnode;

	lastnode = *env;
	while (lastnode->next != NULL)
		lastnode = lastnode->next;
	return (lastnode);
}

char	*ft_strdup_unset(const char *s1)
{
	size_t	i;
	char	*s2;
	char	*s;

	if (!s1)
		return (NULL);
	s2 = (char *)s1;
	s = (char *)malloc(sizeof(char) * ft_strlen(s2) + 1);
	i = 0;
	if (!s)
		return (0);
	while (i < ft_strlen(s2) && s2[i] != '=')
	{
		s[i] = s2[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	size_stack(t_env *head)
{
	int	a;

	a = 0;
	while (head)
	{
		a++;
		head = head->next;
	}
	return (a);
}

void	check_add(t_env **head, t_builtin *arr)
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
				free(new_node->name);
				new_node->name = ft_strdup(arr->name);
				free(new_node->value);
				new_node->value = ft_strdup(arr->value);
			}
			free(arr->new_name);
			arr->c = 1;
			break ;
		}
		free(arr->new_name);
		new_node = new_node->next;
	}
	free(arr->line);
}

int	*check_path(t_builtin *arr, char **add, t_env **new_node)
{
	int	a;

	arr->a = 1;
	arr->add_c = 0;
	arr->add_a = 1;
	while (add[arr->add_a])
		arr->add_a++;
	arr->add_b = malloc((arr->add_a) * (sizeof(int)));
	while (add[arr->a])
	{
		arr->b = 0;
		a = 0;
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b] == '=' || add[arr->a][arr->b] == ' ')
				break ;
			a = check_char(arr, add, new_node);
			if (a != 0)
				break ;
			arr->b++;
		}
		arr->add_b[arr->add_c++] = a;
		arr->a++;
	}
	return (arr->add_b);
}
