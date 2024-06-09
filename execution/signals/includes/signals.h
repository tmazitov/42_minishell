/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 00:13:35 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../../libft/libft.h"

typedef enum status_flag
{
	GET = 1,
	SET = 2,
	GET_HISTORY = 3,
	SET_HISTORY = 4
}		t_status_flag;

typedef enum status
{
	IN_CMD = 20,
	IN_HEREDOC = 40,
	CTRL_C = 130,
	CTRL_BS = 131,
	STOP_HEREDOC = 1,
}		t_status;

int		status_code(t_status_flag flag, int value);

// Signals part

void	sigint_handler(int signum);
void	setup_read_interrupter(void);
void	setup_shell_quit(void);

#endif