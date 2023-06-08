/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:44:04 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/01 13:54:18 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//char	*delete_quotes(char *str)
//{
//	int		i;
//	int		j;
//	char	*new;

//	i = 0;
//	j = 0;
//	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
//	while (str[i])
//	{
//		if (str[i] != '\'' && str[i] != '\"')
//		{
//			new[j] = str[i];
//			j++;
//		}
//		i++;
//	}
//	new[j] = '\0';
//	return (new);
//}

// expand inside quotes

char	*expand_inside_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '$')
		{
			new[j] = str[i];
			j++;
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
			{
				new[j] = str[i];
				j++;
				i++;
			}
		}
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

// main to test the function using loop with readline

//int main()
//{
//	char *str;
//	char *new;

//	while (1)
//	{
//		str = readline("enter a string : ");
//		new = expand_inside_quotes(str);
//		printf("new string : %s\n", new);
//	}
//	return (0);
//}
