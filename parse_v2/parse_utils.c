/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:55:40 by oait-bad          #+#    #+#             */
/*   Updated: 2023/07/25 13:34:24 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_whitespaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}