/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:37:31 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/20 10:11:23 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PIPE 1
# define LESSER 2
# define GREATER 3
# define LEFT_PAR 4
# define RIGHT_PAR 5
# define DOLLAR_SIGN 6
# define QUEST_MARK 7
# define ASTERISK 8
# define SINGLE_QUOTE 9
# define DOUBLE_QUOTE 10
# define SPACE 11
# define HEREDOC 12
# define APPEND 13
# define WORD 14

typedef struct s_lexer
{
	char			*input;
	int				i;
	int				type;
	char			*value;
	struct s_lexer	*tokens;
	struct s_lexer	*current_token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

int	check_tokens(t_lexer *lexer, t_lexer **token);
void	print_tokens(t_lexer *lexer);
int	check_quotes(t_lexer *lexer, t_lexer **token);
t_lexer	*the_lexer(char *input);
char	*check_words(t_lexer *lexer, int *index);
int	node_init(t_lexer **token);

#endif