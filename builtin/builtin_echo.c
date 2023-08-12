/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:15:52 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 08:01:13 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_space(char **av, t_builtin *arr)
{
	char	*p;

	arr->b = 0;
	arr->c = 0;
	while (av[arr->a])
	{
		p = delete_quotes(av[arr->a]);
		if (ft_strncmp(p, "-n", 2) == 0)
		{
			arr->x = 1;
			while (p[arr->x])
			{
				if (p[arr->x] != 'n')
					return (arr->b);
				arr->x++;
			}
				arr->a++;
				arr->b = 1;
				arr->c++;
		}
		else
			break ;
	}
	free(p);
	return (arr->b);
}

void	builtin_echo(char **av, t_builtin *arr)
{
	char	*p;

	arr->a = 1;
	free(arr->cmd_ns);
	g_exit_value = 0;
	if (av[arr->a] == NULL)
	{
		printf("\n");
		return ;
	}
	arr->b = echo_space(av, arr);
	while (av[arr->a])
	{
		p = delete_quotes(av[arr->a]);
		printf("%s", p);
		if (arr->a < arr->args - 1)
			printf(" ");
		free(p);
		arr->a++;
	}
	if (!arr->c)
		printf("\n");
}
