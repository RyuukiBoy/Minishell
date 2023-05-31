/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:28 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/27 13:49:37 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int argc, char **argv, char **env)
//{
//	char	*line;
//	t_lexer	*lexer;
//	t_lexer	*token;
//	//t_env	*envp;
//	//int		i;
//	//int		j;

//	(void)argc;
//	(void)argv;
//	(void)env;
//	lexer = (t_lexer *)malloc(sizeof(t_lexer));
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		lexer->input = line;
//		lexer->i = 0;
//		lexer->tokens = 0;
//		lexer->current_token = 0;
//		token = the_lexer(line);
//		token = lexer->tokens;
//		while (token)
//		{
//			printf("type: %d\n", token->type);
//			printf("value: %s\n", token->value);
//			token = token->next;
//		}
//	}
//	return (0);
//}
