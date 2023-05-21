/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bad <oait-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:41:37 by oait-bad          #+#    #+#             */
/*   Updated: 2023/05/12 10:45:41 by oait-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void *))
{
	t_list	*p;
	t_list	*new;
	t_list	*head;

	if (!lst || !f)
		return (0);
	p = lst;
	head = ft_lstnew(f(p->content));
	if (!head)
		return (0);
	p = p->next;
	while (p)
	{
		new = ft_lstnew(f(p->content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, new);
		p = p->next;
	}
	return (head);
}
