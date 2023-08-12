/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:44:04 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/12 08:44:02 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_riplice(char c, int quotes_type)
{
	if (c == 0)
	{
		if (quotes_type == 1)
			return ('\"');
		else if (quotes_type == 0)
			return ('\'');
	}
	else
	{
		if (quotes_type == 1 && c == '\"')
			return (0);
		else if (quotes_type == 0 && c == '\'')
			return (0);
	}
	return (c);
}

int	check_quotes(char *str)
{
	t_quote	q;

	q = (t_quote){0, 0, 0, 0};
	while (str[q.i])
	{
		if (str[q.i] == '\"' && q.c != '\'')
		{
			q.c = ft_riplice(q.c, 1);
			q.i_len++;
		}
		else if (str[q.i] == '\'' && q.c != '\"')
		{
			q.c = ft_riplice(q.c, 0);
			q.o_len++;
		}
		q.i++;
	}
	if (q.o_len % 2 != 0 || q.i_len % 2 != 0)
	{
		printf("minishell: unclosed quotes\n");
		return (0);
	}
	return (1);
}

void	norm_things(char *str, t_norm *var)
{
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] != '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] != '\"'))
	{
		var->flag = 0;
		var->i++;
	}
}

void	init_var(t_norm *var)
{
	var->i = 0;
	var->j = 0;
	var->flag = 0;
}

char	*delete_quotes(char *str)
{
	t_norm	var;

	init_var(&var);
	if (str == NULL)
		return (NULL);
	norm_things(str, &var);
	var.new = malloc(ft_strlen(str) + 1);
	while (str[var.i])
	{
		if (str[var.i] == '\"' && var.flag == 0)
			var.flag = 1;
		else if (str[var.i] == '\"' && var.flag == 1)
			var.flag = 0;
		else if (str[var.i] == '\'' && var.flag == 0)
			var.flag = 2;
		else if (str[var.i] == '\'' && var.flag == 2)
			var.flag = 0;
		else
			var.new[var.j++] = str[var.i];
		var.i++;
	}
	var.new[var.j] = '\0';
	return (var.new);
}
