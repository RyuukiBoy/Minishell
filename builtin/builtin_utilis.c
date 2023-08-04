/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:07:11 by ybargach          #+#    #+#             */
/*   Updated: 2023/06/13 11:28:01 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_add(t_env **head, t_builtin *arr)
{
	t_env	*new_node;

	arr->c = 0;
	new_node = *head;
	while (new_node != NULL)
	{
		arr->new_name = ft_strdup_unset(new_node->name);
		arr->line = ft_strdup_unset(arr->name);
		if (strcmp(arr->new_name, arr->line) == 0)
		{
			if (arr->value != NULL)
			{
				new_node->name = arr->name;
				new_node->value = arr->value;
			}
			arr->c = 1;
		}
		free(arr->new_name);
		free(arr->line);
		new_node = new_node->next;
	}
	return (arr->c);
}

void	check_after_back(t_builtin *arr, char **add)
{
	if (!((add[arr->a][arr->b + 1] >= 'a' && add[arr->a][arr->b + 1] <= 'z')
		|| (add[arr->a][arr->b + 1] >= 'A' && add[arr->a][arr->b + 1] <= 'Z')
		|| (add[arr->a][arr->b + 1] >= '0' && add[arr->a][arr->b + 1] <= '9')
		|| add[arr->a][arr->b + 1] == '_'))
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		exit(1);
	}
	else
		exit(0);
}

void	check_path(t_builtin *arr, char **add)
{
	arr->a = 0;
	while (add[arr->a])
	{
		arr->b = 0;
		check_first_char(arr, add);
		while (add[arr->a][arr->b])
		{
			if (add[arr->a][arr->b] == '=')
				break ;
			if (add[arr->a][arr->b] == '\\')
				check_after_back(arr, add);
			check_char(arr, add);
			arr->b++;
		}
		arr->a++;
	}
}
