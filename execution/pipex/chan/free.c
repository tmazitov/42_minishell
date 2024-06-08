/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:05:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 00:16:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

void	*free_log_chan(t_log_chan *chan)
{
	int	counter;

	if (!chan)
		return (NULL);
	counter = 0;
	while (chan->side && counter < chan->side_count)
	{
		if (chan->side[counter] != -1)
			close(chan->side[counter]);
		counter++;
	}
	if (chan->side)
		free(chan->side);
	free(chan);
	return (NULL);
}
