/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:03:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/30 14:23:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

int	status_code(t_status_flag flag, int new_status)
{
	static int	status;

	if (flag == GET)
		return (status);
	else if (flag == SET)
		status = new_status;
	return (status);
}


