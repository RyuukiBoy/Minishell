/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:55:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/10 15:51:14 by ybargach         ###   ########.fr       */
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
