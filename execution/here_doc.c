/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybargach <ybargach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:03:35 by ybargach          #+#    #+#             */
/*   Updated: 2023/08/12 20:14:46 by ybargach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_here(char const *s1, char const *s2)
{
	char	*p;
	int		d;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (0);
	d = (ft_strlen(s1) + ft_strlen(s2) + 2);
	a = 0;
	b = 0;
	p = malloc(d * sizeof(char));
	if (!p)
		return (0);
	while (s1[b] && d - 1 > a)
	{
		p[a] = s1[b];
		a++;
		b++;
	}
	p[a] = '\0';
	ft_strlcat(p, s2, d);
	return (p);
}

void	here_doc_child(t_builtin *arr, char *args)
{
	char	*p;
	char	*limiter;

	limiter = ft_strjoin_here(args, "\n");
	close(arr->her_p[0]);
	while (1)
	{
		p = readline("> ");
		if (!p || ft_strcmp(args, p) == 0)
			break ;
		write(arr->her_p[1], p, ft_strlen(p));
		ft_putstr_fd("\n", arr->her_p[1]);
		free(p);
	}
	free(p);
	free(limiter);
	close(arr->her_p[1]);
	g_exit_value = 0;
	exit(0);
}

int	here_doc_parent(t_builtin *arr)
{
	int	exit;

	wait(&exit);
	if (WEXITSTATUS(exit) == 69)
		arr->here_exit = 1;
	close(arr->her_p[1]);
	return (arr->her_p[0]);
}

void	exit_status(int number)
{
	if (number == SIGINT)
	{
		exit(69);
	}
}

int	here_doc(t_builtin *arr, char *args)
{
	signal(SIGINT, SIG_IGN);
	if (pipe(arr->her_p) == -1)
	{
		perror("pipe: ");
		g_exit_value = 1;
	}
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork: ");
	if (arr->pid == 0)
	{
		signal(SIGINT, exit_status);
		here_doc_child(arr, args);
	}
	else
		arr->her_f = here_doc_parent(arr);
	close(arr->her_p[1]);
	free(args);
	return (arr->her_f);
}
