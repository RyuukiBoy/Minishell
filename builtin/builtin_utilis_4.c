/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utilis_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:03:23 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 15:55:30 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmp_delete(t_env **head, t_env *tmp, t_env *current)
{
	tmp = current->next;
	*head = tmp;
	free(current->name);
	free(current->value);
	free(current);
	current = tmp;
}

void	cmp_delete_two(t_env *current, t_env *prev)
{
	prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

void	print_exit_multi(char *add)
{
	int	a;
	int	b;

	a = ft_atoi(add);
	b = 0;
	if (a >= 0)
	{
		b = a % 256;
		g_exit_value = b;
	}
	else
	{
		b = (a % 256 + 256) % 256;
		g_exit_value = b;
	}
}

void	print_error_exit(char *add)
{
	printf("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", add);
	g_exit_value = 255;
	exit (255);
}

void	print_exit(char *add)
{
	int	a;
	int	b;

	a = ft_atoi(add);
	if (a >= 0)
	{
		b = a % 256;
		printf("exit\n");
		g_exit_value = b;
	}
	else
	{
		b = (a % 256 + 256) % 256;
		printf("exit\n");
		g_exit_value = b;
	}
	exit(b);
}
