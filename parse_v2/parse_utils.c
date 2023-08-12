/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:55:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/12 09:03:18 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_it(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
}

void	free_exp(t_exp *exp)
{
	free(exp->key);
	free(exp->tmp);
	free(exp->before);
	free(exp->value);
	free(exp->after);
	free(exp);
}

int	is_inside_squotes(char *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (str[j] == '\'')
			return (1);
		j++;
	}
	return (0);
}

void	file_err(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	file_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}
