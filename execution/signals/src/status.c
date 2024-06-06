/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:03:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/06 19:37:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

int	status_code(t_status_flag flag, int new_status)
{
	static int	status_prev;
	static int	status;

	if (flag == GET)
		return (status);
	else if (flag == SET)
		status = new_status;
	else if (flag == SET_HISTORY)
		status_prev = status;
	else if (flag == GET_HISTORY)
		return (status_prev);
	return (status);
}
