/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:46:43 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/23 16:16:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t len)
{
	void	*new_ptr;
	size_t	old_size;

	if (ptr == NULL)
		return (malloc(len));
	if (len == 0)
	{
		free (ptr);
		return (NULL);
	}
	new_ptr = malloc(len);
	if (!new_ptr)
		return (NULL);
	old_size = ft_strlen(ptr);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
