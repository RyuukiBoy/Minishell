/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:34:48 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/21 09:00:29 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	node_init(t_lexer **token)
{
	*token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!*token)
		return (0);
	(*token)->type = 0;
	(*token)->value = 0;
	(*token)->next = 0;
	return (1);
}

int	check_tokens(t_lexer *lexer, t_lexer **token)
{
	if (lexer->input[lexer->i] == '|')
	{
		if (!node_init(token))
			return (0);
		(*token)->type = PIPE;
		(*token)->value = ft_strdup("|");
	}
	else if (lexer->input[lexer->i] == '>')
	{
		if (!node_init(token))
			return (0);
		if (lexer->input[lexer->i + 1] == '>')
		{
			(*token)->type = APPEND;
			(*token)->value = ft_strdup(">>");
			lexer->i += 1;
		}
		else
		{
			(*token)->type = GREATER;
			(*token)->value = ft_strdup(">");
		}
	}
	else if (lexer->input[lexer->i] == '<')
	{
		if (!node_init(token))
			return (0);
		if (lexer->input[lexer->i + 1] == '<')
		{
			(*token)->type = HEREDOC;
			(*token)->value = ft_strdup("<<");
			lexer->i += 1;
		}
		else
		{
			(*token)->type = LESSER;
			(*token)->value = ft_strdup("<");
		}
	}
	else if (lexer->input[lexer->i] == ' ')
	{
		if (!node_init(token))
			return (0);
		(*token)->type = SPACE;
		(*token)->value = ft_strdup(" ");
	}
	return (1);
}

int	check_quotes(t_lexer *lexer, t_lexer **token)
{
	if (lexer->input[lexer->i] == '\'')
	{
		if (!node_init(token))
			return (0);
		(*token)->type = SINGLE_QUOTE;
		(*token)->value = ft_strdup("\'");
		return (1);
	}
	else if (lexer->input[lexer->i] == '\"')
	{
		if (!node_init(token))
			return (0);
		(*token)->type = DOUBLE_QUOTE;
		(*token)->value = ft_strdup("\"");
		return (1);
	}
	return (-1);
}

char	*check_words(t_lexer *lexer, int *index)
{
	char	*str;
	int		i;

	i = *index;
	while (lexer->input[i] && lexer->input[i] != ' ' && lexer->input[i] != '|'
		&& lexer->input[i] != '<' && lexer->input[i] != '>'
		&& lexer->input[i] != '\'' && lexer->input[i] != '\"')
		i++;
	if (i == *index)
		return (0);
	str = ft_substr(lexer->input, *index, i - *index);
	*index = i - 1;
	return (str);
}

void	print_tokens(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
	}
}
