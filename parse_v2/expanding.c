/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:24:37 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 15:15:42 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	char	*value;
	char	*tmp;

	while (env)
	{
		tmp = ft_strjoin(key, "=");
		if (ft_strncmp(env->name, tmp, ft_strlen(tmp)) == 0)
		{
			value = ft_strdup(env->value);
			free(tmp);
			return (value);
		}
		env = env->next;
	}
	return (0);
}

void	norm_ex(t_exp *exp, t_env *envp)
{
	exp->value = get_env_value(exp->key, envp);
	if (!exp->value)
		exp->value = ft_strdup("");
}

void	apply_expander(char **args, t_env *envp, int i, int j)
{
	t_exp	*exp;

	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->before = ft_substr(args[i], 0, ft_strchr(args[i], '$') - args[i]);
	while (args[i][j] && args[i][j] != '$')
		j++;
	while (args[i][j] && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
		j++;
	if (args[i][j] == '$')
	{
		exp->start = ++j;
		while (args[i][j] && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
			j++;
		exp->end = j;
		exp->key = ft_substr(args[i], exp->start, exp->end - exp->start);
		norm_ex(exp, envp);
		exp->after = ft_substr(args[i], exp->end, ft_strlen(args[i])
				- exp->end);
		exp->tmp = ft_strjoin(exp->before, exp->value);
		exp->all_cmd = ft_strjoin(exp->tmp, exp->after);
		free(args[i]);
		args[i] = exp->all_cmd;
		free_exp(exp);
		apply_expander(args, envp, i, 0);
	}
}

void	expand_norm(char **args, t_env *envp, int i, int j)
{
	t_exp	*exp;

	exp = (t_exp *)malloc(sizeof(t_exp));
	if (args[i][j] == '$')
	{
		if (args[i][j + 1] == '?')
		{
			args[i][j] = '\0';
			args[i] = ft_strjoin(args[i], ft_itoa(g_exit_status));
			args[i] = ft_strjoin(args[i], &args[i][j + 2]);
		}
		else if (ft_isdigit(args[i][j + 1]))
		{
			args[i][j] = '\0';
			args[i] = ft_strjoin(args[i], &args[i][j + 2]);
		}
		else if (!is_inside_squotes(args[i], j))
			apply_expander(args, envp, i, j);
	}
}

void	expand(char **args, t_env *envp)
{
	t_exp	*exp;
	int		i;
	int		j;

	i = 0;
	exp = (t_exp *)malloc(sizeof(t_exp));
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			expand_norm(args, envp, i, j);
			j++;
		}
		i++;
	}
}
