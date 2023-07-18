/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 01:55:13 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/17 09:44:52 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_operators(char *cmd, int *type, int i)
{
	if (cmd[0] == '|')
		type[i] = PIPE;
	else if (ft_strlen(cmd) > 1 && cmd[0] == '<')
		type[i] = HEREDOC_SIG;
	else if (ft_strlen(cmd) > 1 && cmd[0] == '>')
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
	int	*type;
	int	i;

	i = 0;
	type = ft_calloc(ft_array_size(cmd) + 1, sizeof(int));
	if (!type)
		return (NULL);
	while (cmd && cmd[i])
	{
		check_after_op(cmd, type, i);
		i++;
	}
	if (check_all_opers(type))
		return (type);
	return (type);
}

//int main()
//{
//	char	*line;
//	char	**cmd;
//	int		*type;
//	int		i;
	
//	i = 0;
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		cmd = split_args(line);
//		type = get_tokens(cmd);
//		while (cmd[i])
//		{
//			printf("cmd[%d] = %s\n", i, cmd[i]);
//			printf("type[%d] = %d\n", i, type[i]);
//			printf("____________________\n");
//			i++;
//		}
//	}
//}