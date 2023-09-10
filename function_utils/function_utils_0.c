/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:48:28 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 14:37:10 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**send_red(char	*str, t_builtin *arr)
{
	arr->y = ft_strlen_double(str, arr);
	arr->a_cmd = malloc((arr->y + 1) * (sizeof(char *)));
	arr->str_b = 0;
	arr->str_c = 0;
	if (str[arr->str_b] == '<' || str[arr->str_b] == '>')
		arr->start_red = arr->str_b;
	while (str[arr->str_b] == '<' || str[arr->str_b] == '>')
	{
		if (str[arr->str_b + 1] != '<' || str[arr->str_b + 1] != '>')
		{
			if (str[arr->str_b + 1] == '<' || str[arr->str_b + 1] == '>')
				arr->str_b++;
			arr->a_cmd[arr->str_c] = sub(str, arr->start_red, (arr->str_b + 1));
			arr->str_c++;
		}
		arr->str_b++;
	}
	while (str[arr->str_b] == '\t' || str[arr->str_b] == ' ')
		arr->str_b++;
	if (str[arr->str_b] == '\t' || str[arr->str_b] == ' '
		|| (check_opera_red(str, arr) == 1) || str[arr->str_b] == '\"'
		|| str[arr->str_b] == '\'')
		arr->a_cmd[arr->str_c++] = last_send_red(str, arr);
	arr->a_cmd[arr->str_c] = NULL;
	return (arr->a_cmd);
}

char	*cpy_cmd(char *cmd, t_builtin *arr)
{
	int		a;
	char	*p;

	a = 0;
	p = malloc(arr->end - arr->start + 1);
	if (!p)
		return (NULL);
	while (arr->start < arr->end)
	{
		p[a] = cmd[arr->start];
		a++;
		arr->start++;
	}
	p[a] = '\0';
	return (p);
}

char	*dlt_cmd(char *cmd, t_builtin *arr)
{
	int		a;
	int		b;
	char	*p;

	a = 0;
	b = 0;
	while (cmd[a])
		a++;
	p = malloc(a - (arr->move_end - arr->move_start) + 1);
	if (!p)
		return (NULL);
	a = 0;
	while (cmd[a])
	{
		if (a >= arr->move_start && a <= arr->move_end)
			a++;
		else
			p[b++] = cmd[a++];
	}
	p[b] = '\0';
	free(cmd);
	return (p);
}

char	*any_cmd(char *cmd, t_builtin *arr, t_all all)
{
	arr->move_b = 0;
	all.fd->infd = 0;
	all.fd->outfd = 1;
	while (cmd[arr->move_b])
	{
		if (all.fd->infd < 0 || all.fd->outfd < 0)
			break ;
		if (cmd[arr->move_b] == '\'' || cmd[arr->move_b] == '"')
			arr->move_b = check_qoutes(cmd, arr);
		if (cmd[arr->move_b] == '<' || cmd[arr->move_b] == '>')
		{
			arr->move_start = arr->move_b;
			after_cmd(cmd, arr, all);
			arr->move_end = arr->move_b;
			cmd = dlt_cmd(cmd, arr);
			arr->move_b = 0;
		}
		else
			arr->move_b++;
	}
	return (cmd);
}
