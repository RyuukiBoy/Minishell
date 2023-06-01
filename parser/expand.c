/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:39:05 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/01 00:43:21 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char *str)
{
	if (*str == '$' || *str == ',' || *str == '.'
		|| *str == '/' || *str == ':' || *str == '=')
		return (1);
	return (0);
}

char	**get_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

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

char	**dollar_sign(char **args, char **env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	char	*tmp;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (*args[i] == '$')
		{
			args[i] = expand_inside_quotes(args[i]);
			key = get_env_key(args[i] + 1);
			value = get_env_value(key, env);
			if (value == NULL)
				value = ft_strdup("");
			tmp = ft_strjoin(value, args[i] + ft_strlen(key) + 1);
			free(args[i]);
			args[i] = tmp;
			free(key);
			free(value);
		}
		i++;
	}
	return (args);
}

//int main(int argc, char **argv, char **env)
//{
//	char	*line;
//	char	**args;
//	char	**envp;
//	int		i;
//	//int		j;

//	(void)argc;
//	(void)argv;
//	envp = get_env(env);
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		args = dollar_sign(ft_split(line, ' '), envp);
//		i = 0;
//		while (args[i])
//		{
//			printf("%s\n", args[i]);
//			i++;
//		}
//		free(line);
//		free(args);
//	}
//}