/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:15:52 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/05 13:59:06 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_space(char **av, t_builtin *arr)
{
	arr->c = 0;
	arr->d = 1;
	if (ft_strncmp(av[1], "-n", 2) == 0)
	{
		arr->b = 1;
		while (av[1][arr->b])
		{
			if (av[1][arr->b] != 'n')
				arr->c++;
			arr->b++;
		}
		if (arr->c == 0)
			arr->d = 0;
		else
			arr->d = 1;
	}
	return (arr->d);
}

void	print_echo(char **av, int args, t_builtin *arr)
{
	while (arr->a < args)
	{
		printf("%s", av[arr->a]);
		if (arr->a != args - 1)
			printf(" ");
		arr->a++;
	}
	if (arr->space == 1)
		printf("\n");
}

void	builtin_echo(char **av, int args, t_builtin	*arr)
{
	arr->a = 1;
	if (av[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	arr->space = echo_space(av, arr);
	if (arr->space == 1)
		arr->a = 1;
	else
		arr->a = 2;
	print_echo(av, args, arr);
}
