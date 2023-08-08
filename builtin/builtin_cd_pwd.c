/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:15:42 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 09:18:00 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_in_env(char *av, char *old_pwd, t_env *env)
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
}
void	builtin_cd(char **av, t_env *env)
{
	char	*cmd;
	char	pwd[1024];
	char	*old;
	int		cd;

	old = getcwd(pwd, 1024);
	if (av[1] == NULL)
	{
		cmd = getenv("HOME");
		cd = chdir(cmd);
		if (cd == -1)
			perror("cd: ");
		else
			change_in_env(cmd, old, env);
		return ;
	}
	cd = chdir(av[1]);
	if (cd == -1)
		printf("cd: %s: No such file or directory", av[1]);
	else
		change_in_env(av[1], old, env);
}

void	builtin_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	if (getcwd(pwd, 1024) != NULL)
		printf("%s\n", pwd);
	else
		perror("pwd");
}
