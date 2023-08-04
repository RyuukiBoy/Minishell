/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:44:04 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/27 18:17:49 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unclosed_quotes(char *str)
{
	int		i;
	int		single;
	int		doubleq;

	i = 0;
	single = 0;
	doubleq = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single++;
		if (str[i] == '\"')
			doubleq++;
		i++;
	}
	if (single % 2 != 0 || doubleq % 2 != 0)
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
//		new = delete_quotes(line);
//		printf("%s\n", new);
//	}
//}