/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:39:05 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/25 14:29:28 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_env(char **env)
{
	int		i;
	char	**envp;

	i = 0;
	while (env[i])
		i++;
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		envp[i] = ft_strdup(env[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(key) + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*dollar_sign(char *str, char **env)
{
	char	*value;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && str[j] != ' ' && str[j] != '$')
				j++;
			tmp = ft_substr(str, 0, i);
			value = get_env_value(ft_substr(str, i + 1, j - i - 1), env);
			if (!value)
				value = ft_strdup("");
			tmp2 = ft_substr(str, j, ft_strlen(str) - j);
			str = ft_strjoin(tmp, value);
			str = ft_strjoin(str, tmp2);
			free(tmp);
			free(tmp2);
			free(value);
		}
		i++;
	}
	return (str);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*str;
	char	**envp;
	int		i;
	int		j;

	(void)argc;
	(void)argv;
	envp = get_env(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		str = dollar_sign(line, envp);
		if (ft_strncmp(str, "env", 3) == 0)
		{
			i = 0;
			while (envp[i])
			{
				printf("%s\n", envp[i]);
				i++;
			}
		}
		else
			printf("%s\n", str);
	}
	return (0);
}