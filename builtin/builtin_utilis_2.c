/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:14:37 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/05 13:28:43 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_equal(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	a;
	unsigned int	b;

	a = start;
	b = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	if (start > (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (s[a] && b < len)
	{
		if (s[a] == '+')
			a++;
		p[b] = s[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}

char	*ft_join_utils(char const *s1, char const *s2)
{
	char	*p;

	p = NULL;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
	{
		p = ft_strdup(s2);	
		return (p);
	}
	else if (s1 && !s2)
	{
		p = ft_strdup(s1);;
		return (p);
	}
	return (p);
}

char	*ft_strjoin_equal(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (ft_join_utils(s1, s2));
	d = (ft_strlen(s1) + ft_strlen(s2) + 2);
	a = 0;
	b = 0;
	p = malloc(d * sizeof(char));
	if (!p)
		return (0);
	while (s1[b] && d - 1 > a)
	{
		p[a] = s1[b];
		a++;
		b++;
	}
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}

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
				arr->value = ft_strjoin_equal(new_node->value, arr->value);
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
			free(value);
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

int	check_char(t_builtin *arr, char **add, t_env **new_node)
{
	if ((add[arr->a][arr->b] >= 'a' && add[arr->a][arr->b] <= 'z')
		|| (add[arr->a][arr->b] >= 'A' && add[arr->a][arr->b] <= 'Z')
		|| (add[arr->a][arr->b] >= '0' && add[arr->a][arr->b] <= '9')
		|| add[arr->a][arr->b] == '_' || add[arr->a][arr->b] == '+')
	{
		if ((add[arr->a][arr->b] == '+' && add[arr->a][arr->b + 1] != '='))
		{
			ft_putstr_fd(add[arr->a], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			//exit(1);
			return (-1);
		}
		else if ((add[arr->a][arr->b] == '+' && add[arr->a][arr->b + 1] == '='))
		{
			export_equal(arr, add[arr->a], new_node);
			return (1);
		}
	}
	else
	{
		ft_putstr_fd(add[arr->a], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		//exit(1);
		return (-1);
	}
	return (0);
}
