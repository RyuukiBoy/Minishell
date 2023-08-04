/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:02:16 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/03 15:01:44 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_err(char *file, int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

void	redirect(char **cmd, t_iof *file)
{
	int		i;

	i = 0;
	if (strcmp(cmd[i], ">") == 0)
	{
		file->outfd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_err(cmd[i + 1], file->outfd))
			return ;
		close(file->outfd);
	}
	else if (strcmp(cmd[i], ">>") == 0)
	{
		file->outfd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_err(cmd[i + 1], file->outfd))
			return ;
		close(file->outfd);
	}
	else if (strcmp(cmd[i], "<") == 0)
	{
		file->infd = open(cmd[i + 1], O_RDONLY);
		if (file_err(cmd[i + 1], file->infd))
			return ;
		close(file->infd);
	}
	i++;
}
