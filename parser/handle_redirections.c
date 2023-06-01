/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:14:56 by oait-bad          #+#    #+#             */
/*   Updated: 2023/06/01 13:32:08 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], ">") == 0)
			handle_redirections_out(cmd, i);
		//else if (ft_strcmp(cmd->args[i], ">>") == 0)
		//	handle_redirections_out_append(cmd, i);
		//else if (ft_strcmp(cmd->args[i], "<") == 0)
		//	handle_redirections_in(cmd, i);
		//else if (ft_strcmp(cmd->args[i], "<<") == 0)
		//	handle_redirections_in_heredoc(cmd, i);
		i++;
	}
}