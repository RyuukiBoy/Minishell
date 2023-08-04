/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:48:28 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/03 15:03:30 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_send_red(char *str, t_builtin *arr)
{
	char	*cmd;

	while (str[arr->str_b] == ' ' || str[arr->str_b] == '\t')
			arr->str_b++;
	while ((str[arr->str_b + 1] >= 'a' && str[arr->str_b + 1] <= 'z'))
		arr->str_b++;
	cmd = ft_substr(str, arr->start_red, arr->str_b);
	return (cmd);
}

char	**send_red(char	*str, t_builtin *arr)
{
	char	**cmd;

	arr->y = ft_strlen_double(str, arr);
	cmd = malloc((arr->y + 1) * (sizeof(char *)));
	arr->str_b = 0;
	arr->str_c = 0;
	arr->start_red = arr->str_b;
	if (str[arr->str_b] == '<' || str[arr->str_b] == '>')
	{
		while (str[arr->str_b + 1] == '<' || str[arr->str_b + 1] == '>')
			arr->str_b++;
		cmd[arr->str_c] = ft_substr(str, arr->start_red, (arr->str_b + 1));
		arr->str_b++;
		arr->start_red = arr->str_b;
		arr->str_c++;
	}
	if ((str[arr->str_b] == '\t' || str[arr->str_b] == ' ' )||
		(str[arr->str_b] >= 'a' && str[arr->str_b] <= 'z'))
	{
		cmd[arr->str_c] = last_send_red(str, arr);
		arr->str_c++;
	}
	cmd[arr->str_c] = NULL;
	return (cmd);
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

void	after_cmd(char *cmd, t_builtin *arr, t_iof *fd)
{
	char	*n_cmd;
	char	**finl;

	arr->start = arr->move_b;
	while (cmd[arr->move_b])
	{
		if (cmd[arr->move_b + 1] == ' ' || cmd[arr->move_b + 1] == '\t'
			|| cmd[arr->move_b + 1] == '\0')
		{
			if ((cmd[arr->move_b] >= 'a' && cmd[arr->move_b] <= 'z')
				|| (cmd[arr->move_b + 1] == '\0'))
			{
				arr->end = arr->move_b + 1;
				n_cmd = cpy_cmd(cmd, arr);
				finl = send_red(n_cmd, arr);
				redirect(finl, fd);
				return ;
			}
		}
		arr->move_b++;
	}
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
	p = malloc(a - (arr->move_end - arr->move_start));
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

char	*any_cmd(char *cmd, t_builtin *arr, t_iof *fd)
{
	char	*n_cmd;

	arr->move_b = 0;
	fd->infd = 0;
	fd->outfd = 1;
	while (cmd[arr->move_b])
	{
		if (cmd[arr->move_b] == '<' || cmd[arr->move_b] == '>')
		{
			fd->infd = 0;
			fd->outfd = 1;
			arr->move_start = arr->move_b;
			after_cmd(cmd, arr, fd);
			arr->move_end = arr->move_b;
			cmd = dlt_cmd(cmd, arr);
			arr->move_b = 0;
		}
		else
			arr->move_b++;
	}
	return (cmd);
}
