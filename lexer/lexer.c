/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:07:07 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/03 10:31:08 by oait-bad         ###   ########.fr       */
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

t_lexer	*the_lexer(char *input)
{
	int		check;
	char 	*word;
	t_lexer	*lexer;
	t_lexer	*token;
	t_lexer	*new_token;

	if (!lexer_init(&lexer, input))
		return (0);
	while (lexer->input[lexer->i])
	{
		word = check_words(lexer, &(lexer->i));
		if (word)
		{
			new_token = (t_lexer *)malloc(sizeof(t_lexer));
			if (!node_init(&token))
				return (0);
			new_token->type = WORD;
			new_token->value = word;
			new_token->next = 0;
			if (!lexer->tokens)
				lexer->tokens = new_token;
			else
			{
				lexer->current_token->next = new_token;
				lexer->current_token = new_token;
			}
			lexer->current_token = new_token;
			if (lexer->input[lexer->i + 1] == '\0')
				break ;
		}
		check = check_quotes(lexer, &token);
		if (!check && lexer->input[lexer->i] == '\0')
			break ;
		if (check == -1 && !check_tokens(lexer, &token))
			break ;
		if (!lexer->tokens)
			lexer->tokens = token;
		else
			lexer->current_token->next = token;
		lexer->current_token = token;
		lexer->i++;
	}
	return (lexer);
}
