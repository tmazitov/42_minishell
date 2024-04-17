/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:07:41 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*p;

	if (size && number && (number > (SIZE_MAX / size)))
		return (NULL);
	if (size == INT_MAX && number == INT_MAX)
		return (NULL);
	p = malloc(number * size);
	if (!p)
		return (NULL);
	ft_bzero(p, number * size);
	return (p);
}
