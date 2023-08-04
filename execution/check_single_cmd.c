/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:45:08 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 10:17:36 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**put_env_array(t_env **new_env, t_builtin *arr, int space)
{
	char	**env;
	t_env	*new_list;

	new_list = (*new_env);
	arr->a = 0;
	env = malloc(sizeof(char *) * space);
	while (new_list != NULL)
	{
		env[arr->a] = ft_strjoin(new_list->name, new_list->value);
		arr->a++;
		new_list = new_list->next;
	}
	return (env);
}

int	size_list(t_env **new_env, t_builtin *arr)
{
	t_env	*size;

	size = *new_env;
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

	env = (*new_env);
	arr->a = 0;
	while (env)
	{
		if (ft_strncmp(env->name, "PATH=", 5) == 0)
		{
			arr->path1 = env->name;
			arr->path2 = env->value;
		}
		env = env->next;
	}
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

void	single_here_doc(t_builtin *arr, char **args)
{
	char	*p;
	char	*limiter;

	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork: ");
	if (arr->pid == 0)
	{
		limiter = ft_strjoin(args[0], "\n");
		while (1)
		{
			ft_putstr_fd("here_doc > ", 1);
			p = get_next_line(0);
			if (!p || strcmp(limiter, p) == 0)
				break ;
			free(p);
		}
		free(limiter);
		exit (0);
	}
	else
		wait(NULL);
}
