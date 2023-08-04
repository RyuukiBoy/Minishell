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

void	builtin_cd(char **av)
{
	char	*cmd;

	if (av[1] == NULL)
	{
		cmd = getenv("HOME");
		if (chdir(cmd) == -1)
			perror("cd");
		return ;
	}
	if (chdir(av[1]) == -1)
		perror("cd");
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
