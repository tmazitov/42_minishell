/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:46:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 02:22:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

t_com_output	*get_last_output(t_com_output_storage *storage)
{
	int	last_index;

	if (!storage || !storage->content || storage->total_amount == 0)
		return (NULL);
	last_index = storage->total_amount - 1;
	return (storage->content[last_index]);
}
