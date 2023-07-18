/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:24:37 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/18 01:52:29 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *key, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		tmp = ft_strjoin(key, "=");
		if (ft_strnstr(env[i], tmp, ft_strlen(tmp)))
		{
			value = ft_strdup(env[i] + ft_strlen(tmp));
			free(tmp);
			return (value);
		}
		free(tmp);
		i++;
	}
	return (0);
}

char	*get_env_key(char *input)
{
	int		i;
	char	*key;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (input[i] && input[i] != '=')
	{
		key[i] = input[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	expand(char **args, char **env, int i, int j)
{
	t_exp	*exp;

	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->before = ft_substr(args[i], 0, ft_strchr(args[i], '$') - args[i]);
	while (args[i][j] && args[i][j] != '$')
		j++;
	exp->start = ++j;
	while (args[i][j] && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
		j++;
	exp->end = j;
	exp->key = ft_substr(args[i], exp->start, exp->end - exp->start);
	exp->value = get_env_value(exp->key, env);
	if (!exp->value)
		exp->value = ft_strdup("");
	free(exp->key);
	exp->after = ft_substr(args[i], exp->end, ft_strlen(args[i]) - exp->end);
	exp->tmp = ft_strjoin(exp->before, exp->value);
	exp->all_cmd = ft_strjoin(exp->tmp, exp->after);
	free(args[i]);
	args[i] = exp->all_cmd;
	free(exp->tmp);
	free(exp->before);
	free(exp->after);
}

char	**dollar_sign(char **args, char **env)
{
	int		i;
	int		j;
	t_exp	*exp;

	i = 0;
	exp = (t_exp *)malloc(sizeof(t_exp));
	while (args[i])
	{
		j = 0;
		if (ft_strchr(args[i], '$'))
		{
			if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				exp->value = ft_itoa(g_exit_status);
				exp->all_cmd = ft_strjoin(exp->value, args[i] + 2);
				free(args[i]);
				args[i] = exp->all_cmd;
			}
			else if (args[i][j] == '$' && ft_isdigit(args[i][j + 1]))
			{
				exp->value = ft_strdup("");
				exp->all_cmd = ft_strjoin(exp->value, args[i] + 2);
				free(args[i]);
				args[i] = exp->all_cmd;
			}
			else
				expand(args, env, i, j);
		}
		i++;
	}
	return (args);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	int		i;
	//int		j;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		args = dollar_sign(split_args(line), env);
		i = 0;
		while (args[i])
		{
			printf("%s\n", delete_quotes(args[i]));
			i++;
		}
		free(line);
		free(args);
	}
}