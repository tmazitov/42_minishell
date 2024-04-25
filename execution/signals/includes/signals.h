/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/25 15:34:49 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

// Status part

typedef enum
{
	GET = 1,
	SET = 2,
}		t_status_flag;

int	status_code(t_status_flag flag, int value);

// Signals part

void	sigint_handler(int signum);
void	setup_read_interrupter();

#endif