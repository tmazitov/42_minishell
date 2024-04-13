/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_relay.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:57:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/13 18:03:09 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_log_chan	*make_relay_chan(int fd)
{
	t_log_chan	*chan;

	if (fd <= 0)
		return (NULL);
	chan = malloc(sizeof(t_log_chan));
	if (!chan)
		return (NULL);
	chan->side_count = 1;
	chan->side = malloc(sizeof(int) * chan->side_count);
	if (!chan->side)
		return (free_log_chan(chan));
	chan->side[0] = fd;
	return (chan);
}

t_log_chan	*relay_chan_add(t_log_chan *chan, int fd)
{
	int	*old_side;
	int	counter;

	if (fd <= 0)
		return (NULL);
	old_side = chan->side;
	chan->side_count += 1;
	chan->side = malloc(sizeof(int) * chan->side_count);
	if (!chan->side)
		return (free_log_chan(chan));
	counter = 0;
	while (counter < chan->side_count - 1)
	{
		chan->side[counter] = old_side[counter]; 
		counter++;
	}
	free(old_side);
	chan->side[counter] = fd;
	return (chan);
}