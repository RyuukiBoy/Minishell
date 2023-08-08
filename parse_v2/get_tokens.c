/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:55:13 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 15:19:26 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_operators(char *cmd, int *type, int i)
{
	int	j;

	j = 0;
	if (cmd[0] == '|')
		type[i] = PIPE;
	else if (ft_strlen(cmd) > 1 && (cmd[j] == '<' && cmd[j + 1] == '<'))
		type[i] = HEREDOC_SIG;
	else if (ft_strlen(cmd) > 1 && (cmd[j] == '>' && cmd[j + 1] == '>'))
		type[i] = R_APP_SIG;
	else if (cmd[0] == '<')
		type[i] = R_IN_SIG;
	else if (cmd[0] == '>')
		type[i] = R_OUT_SIG;
}

void	check_after_op(char **cmd, int *type, int i)
{
	if (cmd[i][0] == '|' || cmd[i][0] == '<' || cmd[i][0] == '>')
		define_operators(cmd[i], type, i);
	else if (i > 0 && type[i - 1] == R_IN_SIG)
		type[i] = R_IN_FILE;
	else if (i > 0 && type[i - 1] == R_OUT_SIG)
		type[i] = R_OUT_FILE;
	else if (i > 0 && type[i - 1] == R_APP_SIG)
		type[i] = R_APP_FILE;
	else if (i > 0 && type[i - 1] == HEREDOC_SIG)
		type[i] = HEREDOC_LIM;
	else
		type[i] = ARG;
}
// " /\\&|;<>\"'(){}[]$=#\`"

int	ft_array_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	return (i);
}

int	*get_tokens(char **cmd)
{
	int		*type;
	int		i;

	i = 0;
	type = ft_calloc(ft_array_size(cmd) + 1, sizeof(int));
	if (!type)
		return (NULL);
	while (cmd && cmd[i])
	{
		check_after_op(cmd, type, i);
		i++;
	}
	return (type);
}

//int main(int ac, char **av, char **env)
//{
//	t_env	*head;
//	t_env	*new_env;
//	t_builtin	*arr;
//	char	**cmd;
//	int		*type;

//	check_av_ac(ac, av);
//	type = malloc(sizeof(int));
//	head = NULL;
//	arr = (t_builtin *)malloc(sizeof(t_builtin));
//	arr->xa = dup(0);
//	arr->ya = dup(1);
//	new_env = builtin_env(env, arr, &head);
//	arr->d = 0;
//	while (1)
//	{
//		dup2(arr->xa, 0);
//		dup2(arr->ya, 1);
//		arr->first_line = readline(KRED"minihell$ "KWHT);
//		if (!arr->first_line)
//			break ;
//		add_history(arr->first_line);
//		cmd = ft_split_qoutes(arr->first_line, '|');
//		check_cmd(cmd, arr, &head);
//		free(arr->first_line);
//		arr->d++;
//	}
//}
