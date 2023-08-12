/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:51:03 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/10 14:18:04 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sub(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	a;
	unsigned int	b;

	a = start;
	b = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	if (start > (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (s[a] && b < len)
	{
		p[b] = s[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}

void	after_cmd_space(char *cmd, t_builtin *arr)
{
	if (cmd[arr->move_b + 1] == '\0')
		arr->move_b++;
	if (check_opera_quotes(cmd, arr) == 1)
	{
		arr->end = arr->move_b + 1;
		arr->j = 1;
	}
}

void	after_cmd_quotes(char *cmd, t_builtin *arr)
{
	arr->move_b = check_qoutes(cmd, arr) + 1;
	if (cmd[arr->move_b] == ' ' || cmd[arr->move_b] == '\t'
		|| cmd[arr->move_b] == '\0')
	{
		arr->end = arr->move_b;
		arr->j = 1;
	}
}

void	after_cmd_chara(char *cmd, t_builtin *arr)
{
	while (cmd[arr->move_b])
	{
		if (cmd[arr->move_b] == '>' || cmd[arr->move_b] == '<'
			|| cmd[arr->move_b + 1] == '\0' || cmd[arr->move_b] == ' '
			|| cmd[arr->move_b] == '\t')
			break ;
		arr->move_b++;
	}
	if (cmd[arr->move_b + 1] == '\0')
		arr->move_b++;
	if (cmd[arr->move_b] == '>' || cmd[arr->move_b] == '<')
	{
		arr->move_b--;
		arr->end = arr->move_b + 1;
	}
	else
		arr->end = arr->move_b;
	arr->j = 1;
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
			after_cmd_space(cmd, arr);
		else if (cmd[arr->move_b] == '\"' || cmd[arr->move_b] == '\'')
			after_cmd_quotes(cmd, arr);
		else if (check_opera_string(cmd, arr) == 1)
			after_cmd_chara(cmd, arr);
		if (arr->j == 1)
		{
			n_cmd = cpy_cmd(cmd, arr);
			finl = send_red(n_cmd, arr);
			redirect(finl, arr, all);
			ft_free_double(finl);
			free(n_cmd);
			return ;
		}
		arr->move_b++;
	}
}
