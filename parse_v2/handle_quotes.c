/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:44:04 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 11:17:54 by oait-bad         ###   ########.fr       */
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

	q = (t_quote){0, 0, 0};
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

char	*delete_quotes(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*new;

	i = 0;
	j = 0;
	flag = 0;
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] != '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] != '\"'))
	{
		flag = 0;
		i++;
	}
	new = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\"' && flag == 0)
			flag = 1;
		else if (str[i] == '\"' && flag == 1)
			flag = 0;
		else if (str[i] == '\'' && flag == 0)
			flag = 2;
		else if (str[i] == '\'' && flag == 2)
			flag = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

//int main()
//{
//	char	*line;
//	char	*new;

//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (line == NULL)
//			break ;
//		if (check_quotes(line))
//			continue ;
//	}
//}