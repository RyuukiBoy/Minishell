/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:45:08 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/06 11:56:56 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**put_env_array(t_env **new_env, t_builtin *arr, int space)
{
	char	**env;
	t_env	*new_list;

	new_list = (*new_env);
	arr->a = 0;
	env = malloc(sizeof(char *) * (space + 1));
	while (new_list != NULL)
	{
		env[arr->a] = ft_strjoin(new_list->name, new_list->value);
		arr->a++;
		new_list = new_list->next;
	}
	env[arr->a] = NULL;
	return (env);
}

int	size_list(t_env *new_env, t_builtin *arr)
{
	t_env	*size;

	if (new_env == NULL)
		return (0);
	size = new_env;
	arr->a = 0;
	while (size != NULL)
	{
		arr->a++;
		size = size->next;
	}
	return (arr->a);
}

char	*ft_strjoin_exe(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (0);
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
	p[a++] = '/';
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}

char	**check_env_path(t_env **new_env, t_builtin *arr)
{
	t_env	*env;

	if (*new_env == NULL || new_env == NULL)
		return (NULL);
	env = (*new_env);
	arr->a = 0;
	arr->path1 = NULL;
	arr->path2 = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, "PATH=") == 0)
		{
			arr->path1 = env->name;
			arr->path2 = env->value;
			break ;
		}
		env = env->next;
	}
	if (arr->path1 == NULL || arr->path2 == NULL)
		return (NULL);
	arr->path = ft_strjoin(arr->path1, arr->path2);
	arr->split_path = ft_split(arr->path, ':');
	return (arr->split_path);
}

int	size_list_cmd(t_cmd *cmd, t_builtin *arr)
{
	t_cmd	*size;

	size = cmd;
	arr->a = 0;
	while (size != NULL)
	{
		arr->a++;
		size = size->next;
	}
	return (arr->a);
}
