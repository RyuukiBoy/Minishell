/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:02:16 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/27 15:21:49 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_file(t_file *in)
{
	in->fd1 = open(in->file, O_RDONLY);
	if (in->fd1 == -1)
	{
		printf("minishell: %s: %s\n", in->file, strerror(errno));
		return (-1);
	}
	return (0);
}

int	out_file(t_file *out)
{
	out->fd2 = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out->fd2 == -1)
	{
		printf("minishell: %s: %s\n", out->file, strerror(errno));
		return (-1);
	}
	return (1);
}

int	app_file(t_file *app)
{
	app->fd3 = open(app->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (app->fd3 == -1)
	{
		printf("minishell: %s: %s\n", app->file, strerror(errno));
		return (-1);
	}
	return (1);
}

void	close_file(int fd)
{
	if (fd != 0)
		close(fd);
	fd = 0;
}

void	close_files(t_file *files)
{
	close_file(files->fd1);
	close_file(files->fd2);
	close_file(files->fd3);
}

void	parse_files(char **cmd, t_file *files)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "<", 1) == 0)
		{
			files->file = cmd[i + 1];
			if (in_file(files) == -1)
				return ;
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		else if (ft_strncmp(cmd[i], ">", 1) == 0)
		{
			files->file = cmd[i + 1];
			if (out_file(files) == -1)
				return ;
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		else if (ft_strncmp(cmd[i], ">>", 2) == 0)
		{
			files->file = cmd[i + 1];
			if (app_file(files) == -1)
				return ;
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		i++;
	}
}

//int main()
//{
//	char	*line;
//	char	**cmd;
//	t_file	files;

//	files.fd1 = 0;
//	files.fd2 = 0;
//	files.fd3 = 0;
//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			break ;
//		cmd = ft_split(line, ' ');
//		parse_files(cmd, &files);
//		close_files(&files);
//	}
//}