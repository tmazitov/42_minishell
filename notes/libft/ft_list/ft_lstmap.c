/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:10:10 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:24:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	void	*content;

	if (!lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = malloc(sizeof(t_list));
		if (!(node))
		{
			del(content);
			ft_lstclear(&new, (*del));
			return (NULL);
		}
		node->content = content;
		node->next = NULL;
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}
