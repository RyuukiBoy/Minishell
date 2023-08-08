/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:48:28 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/08 10:31:52 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_send_red(char *str, t_builtin *arr)
{
	char	*cmd;
	
	if (str[arr->str_b] == ' ' || str[arr->str_b] == '\t')
		arr->str_b++;
	arr->start_red = arr->str_b;
	while (str[arr->str_b])
	{
		if (str[arr->str_b] == '\"' || str[arr->str_b] == '\'')
			arr->str_b = check_qoutes_red(str, arr);
		if (!(str[arr->str_b + 1] >= 33 && str[arr->str_b + 1] <= 126))
		{
			if (str[arr->str_b + 1] == '\0')
				arr->str_b++;
			break ;
		}
		arr->str_b++;
	}
	cmd = ft_substr(str, arr->start_red, arr->str_b - 1);
	return (cmd);
}

int	check_opera_red(char *cmd, t_builtin *arr)
{
	if (cmd[arr->str_b] >= 42 && cmd[arr->str_b] <= 45)
		return (1);
	else if (cmd[arr->str_b] >= 48 && cmd[arr->str_b] <= 58)
		return (1);
	else if (cmd[arr->str_b] >= 63 && cmd[arr->str_b] <= 91)
		return (1);
	else if (cmd[arr->str_b] >= 93 && cmd[arr->str_b] <= 95)
		return (1);
	else if (cmd[arr->str_b] >= 97 && cmd[arr->str_b] <= 123)
		return (1);
	else if (cmd[arr->str_b] == 33 || cmd[arr->str_b] == 61
		|| cmd[arr->str_b] == 125 || cmd[arr->str_b] == '\0')
		return (1);
	return (0);
}

char	**send_red(char	*str, t_builtin *arr)
{
	char	**cmd;

	arr->y = ft_strlen_double(str, arr);
	cmd = malloc((arr->y + 1) * (sizeof(char *)));
	dprintf(2, "%d\n", arr->y);
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
			cmd[arr->str_c] = ft_substr(str, arr->start_red, (arr->str_b + 1));
			arr->str_c++;
		}
		arr->str_b++;
	}
	while (str[arr->str_b] == '\t' || str[arr->str_b] == ' ')
		arr->str_b++;
	if (str[arr->str_b] == '\t' || str[arr->str_b] == ' ' ||
		(check_opera_red(str, arr) == 1) || str[arr->str_b] == '\"' || str[arr->str_b] == '\'')
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

int	check_opera(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b] >= 42 && cmd[arr->move_b] <= 45)
		return (1);
	else if (cmd[arr->move_b] >= 48 && cmd[arr->move_b] <= 58)
		return (1);
	else if (cmd[arr->move_b] >= 63 && cmd[arr->move_b] <= 91)
		return (1);
	else if (cmd[arr->move_b] >= 93 && cmd[arr->move_b] <= 95)
		return (1);
	else if (cmd[arr->move_b] >= 97 && cmd[arr->move_b] <= 123)
		return (1);
	else if (cmd[arr->move_b] == 33 || cmd[arr->move_b] == 61
		|| cmd[arr->move_b] == 125 || cmd[arr->move_b] == '\0')
		return (1);
	return (0);
}
int	check_opera_quotes(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b - 1] >= 42 && cmd[arr->move_b - 1] <= 45)
		return (1);
	else if (cmd[arr->move_b - 1] >= 48 && cmd[arr->move_b - 1] <= 58)
		return (1);
	else if (cmd[arr->move_b - 1] >= 63 && cmd[arr->move_b - 1] <= 91)
		return (1);
	else if (cmd[arr->move_b - 1] >= 93 && cmd[arr->move_b - 1] <= 95)
		return (1);
	else if (cmd[arr->move_b - 1] >= 97 && cmd[arr->move_b - 1] <= 123)
		return (1);
	else if (cmd[arr->move_b - 1] == 33 || cmd[arr->move_b - 1] == 61
		|| cmd[arr->move_b - 1] == 125 || cmd[arr->move_b] == '\0')
		return (1);
	return (0);
}

void	after_cmd(char *cmd, t_builtin *arr, t_all all)
{
	char	*n_cmd;
	char	**finl;

	arr->start = arr->move_b;
	arr->j = 0;
	while (cmd[arr->move_b])
	{
		if (cmd[arr->move_b] == ' ' || cmd[arr->move_b] == '\t'
			|| cmd[arr->move_b + 1] == '\0')
		{
			if (cmd[arr->move_b + 1] == '\0')
				arr->move_b++;
			if (check_opera_quotes(cmd, arr) == 1)
			{
				arr->end = arr->move_b + 1;
				arr->j = 1;
			}
		}
		else if (cmd[arr->move_b] == '\"' || cmd[arr->move_b] == '\'')
		{
			arr->move_b = check_qoutes(cmd, arr) + 1;
			if (cmd[arr->move_b] == ' ' || cmd[arr->move_b] == '\t'
				|| cmd[arr->move_b] == '\0')
				{
					arr->end = arr->move_b;
					arr->j = 1;
				}
		}
		if (arr->j == 1)
		{
			n_cmd = cpy_cmd(cmd, arr);
			finl = send_red(n_cmd, arr);
			redirect(finl, arr, all);
			return ;
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
	char	*n_cmd;

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
			all.fd->infd = 0;
			all.fd->outfd = 1;
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
