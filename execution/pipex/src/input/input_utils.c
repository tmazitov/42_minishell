/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:51:36 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/07 18:56:42 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_com_input	*get_last_input(t_com_input_storage *storage)
{
	int	last_index;
	if (!storage || !storage->content || storage->total_amount == 0)
		return (NULL);
	last_index = storage->total_amount - 1;
	return (storage->content[last_index]);
}
