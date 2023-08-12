/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:15:42 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:01:06 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_in_env(char *old_pwd, t_env *env)
{
	char	pwd[1024];
	t_env	*new_node;

	new_node = env;
	while (new_node)
	{
		if (ft_strcmp(new_node->name, "PWD=") == 0)
		{
			free(new_node->value);
			new_node->value = ft_strdup(getcwd(pwd, 1024));
		}
		if (ft_strcmp(new_node->name, "OLDPWD=") == 0)
		{
			free(new_node->value);
			new_node->value = ft_strdup(old_pwd);
		}
		new_node = new_node->next;
	}
	g_exit_value = 0;
}

void	builtin_cd_utils(char **av, t_env *env, char *old)
{
	int	cd;

	cd = chdir(av[1]);
	if (cd == -1)
	{
		printf("cd: %s: No such file or directory\n", av[1]);
		g_exit_value = 1;
	}
	else
		change_in_env(old, env);
}

void	builtin_cd(char **av, t_env *env, t_builtin *arr)
{
	char	*cmd;
	char	pwd[1024];
	char	*old;
	int		cd;

	free(arr->cmd_ns);
	old = getcwd(pwd, 1024);
	if (av[1] == NULL)
	{
		cmd = getenv("HOME");
		cd = chdir(cmd);
		if (cd == -1)
		{
			perror("cd: ");
			g_exit_value = 1;
		}
		else
			change_in_env(old, env);
		return ;
	}
	else
	{
		builtin_cd_utils(av, env, old);
		return ;
	}
}

void	builtin_pwd(t_builtin *arr)
{
	char	pwd[1024];

	free(arr->cmd_ns);
	getcwd(pwd, 1024);
	if (getcwd(pwd, 1024) != NULL)
	{
		printf("%s\n", pwd);
		g_exit_value = 0;
	}
	else
	{
		perror("pwd: ");
		g_exit_value = 1;
	}
}
