/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:44:04 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/26 15:24:47 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// set the quotes by the help of lexer.c and parser.c

void	handle_quotes(t_lexer *lexer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(lexer->input);
	while (lexer->input[i])
	{
		if (lexer->input[i] == '\'')
		{
			i++;
			while (lexer->input[i] && lexer->input[i] != '\'')
				i++;
			i++;
		}
		else if (lexer->input[i] == '\"')
		{
			i++;
			while (lexer->input[i] && lexer->input[i] != '\"')
			{
				if (lexer->input[i] == '$')
				{
					i++;
					while (lexer->input[i] && lexer->input[i] != ' ' && lexer->input[i] != '\"')
						i++;
				}
				i++;
			}
			i++;
		}
		else
		{
			tmp[j] = lexer->input[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	lexer->input = ft_strdup(tmp);
	free(tmp);
}

//create a main function to test the function with readline and the lexer

//int main(int argc, char **argv, char **env)
//{
//	char	*line;
//	t_lexer	*lexer;
//	t_lexer	*token;
//	t_env	*envp;
//	char	*str;
//	//int		i;
//	//int		j;

//	(void)argc;
//	(void)argv;
//	lexer = (t_lexer *)malloc(sizeof(t_lexer));
//	envp = (t_env *)malloc(sizeof(t_env));
//	envp->envp = get_env(env);
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		lexer->input = line;
//		lexer->i = 0;
//		lexer->tokens = 0;
//		lexer->current_token = 0;
//		token = lexer->tokens;
//		lexer = the_lexer(line);
//		handle_quotes(lexer);
//		str = dollar_sign(lexer->input, envp);
//	}
//	return (0);
//}
