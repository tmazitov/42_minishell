/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:08:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:24:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_ptr;

	if (!lst)
		return ;
	lst_ptr = lst;
	while (lst_ptr != NULL)
	{
		(*f)(lst_ptr->content);
		lst_ptr = lst_ptr->next;
	}
}
