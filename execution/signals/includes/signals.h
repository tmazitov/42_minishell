/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:55:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/07 12:25:10 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include "../../../libft/libft.h"
// Status part

typedef enum
{
	GET = 1,
	SET = 2,
}		t_status_flag;

typedef enum
{
	IN_CMD = 20,
	IN_HEREDOC = 40,
	CTRL_C = 130,
	CTRL_BS = 131,
	STOP_HEREDOC = 1,
}		t_status;

int	status_code(t_status_flag flag, int value);

// Signals part

void	sigint_handler(int signum);
void	setup_read_interrupter();
void	setup_shell_quit();

#endif