/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:31:32 by oait-bad          #+#    #+#             */
/*   Updated: 2023/08/08 15:31:55 by oait-bad         ###   ########.fr       */
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

void	here_doc_child(t_builtin *arr, t_all all, char *args)
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
	free(args);
	close(arr->her_p[1]);
	//exit_value = 0;
	exit(0);
}

int	here_doc_parent(t_builtin *arr, t_all all, char *args)
{
	int	exit;

	wait(&exit);
	close(arr->her_p[1]);
	//close(arr->her_p[0]);
	return (arr->her_p[0]);
}

int	here_doc(t_builtin *arr, t_all all, char *args)
{
	int		a;
	int		c;
	char	*p;

	c = dup(0);
	a = pipe(arr->her_p);
	if (a == -1)
	{
		perror("pipe: ");
		//exit_value = 1;
	}
	arr->pid = fork();
	if (arr->pid == -1)
		perror("fork: ");
	if (arr->pid == 0)
		here_doc_child(arr, all, args);
	else
		arr->her_f = here_doc_parent(arr, all, args);
	close(arr->her_p[1]);
	dup2(arr->her_f, c);
    return (arr->her_f);
}
