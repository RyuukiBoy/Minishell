/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:07:07 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/21 11:41:49 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer_init(t_lexer **lexer, char *input)
{
	*lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!*lexer)
		return (0);
	(*lexer)->input = input;
	(*lexer)->i = 0;
	(*lexer)->tokens = 0;
	(*lexer)->current_token = 0;
	return (1);
}

//t_lexer	*the_lexer(char *input)
{
	int		check;
	char 	*word;
	t_lexer	*lexer;
	t_lexer	*token;

	if (!lexer_init(&lexer, input))
		return (0);
	while (lexer->input[lexer->i])
	{
		check = check_quotes(lexer, &token);
		if (!check)
			break ;
		if (check == -1 && !check_tokens(lexer, &token))
			break ;
		if (!lexer->tokens)
			lexer->tokens = token;
		else
			lexer->current_token->next = token;
		lexer->current_token = token;
		lexer->i++;
		word = check_words(lexer, &(lexer->i));
		if (word)
		{
			if (!node_init(&token))
				return (0);
			token->type = WORD;
			token->value = word;
			token->next = 0;
			if (!lexer->tokens)
				lexer->tokens = token;
			else
				lexer->current_token->next = token;
			lexer->current_token = token;
			lexer->i++;
		}
	}
	return (lexer);
}

