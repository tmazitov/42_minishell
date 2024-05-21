/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:03:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/21 14:25:28 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int signum)
{
	int	status;

	status = 0;
	if (status != IN_HEREDOC)
		write(STDERR_FILENO, "\n", 1);
	status = status_code(GET, -1);
	if (status == IN_CMD)
	{
		status_code(SET, CTRL_C);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	else if (status == IN_HEREDOC)
	{
		status_code(SET, STOP_HEREDOC);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) signum;
}

void	sigquit_handler(int signum)
{
	int	status;

	status = status_code(GET, -1);
	if (status == IN_CMD)
	{
		status_code(SET, CTRL_BS);
		rl_replace_line("", 0);
		rl_clear_history();
		rl_redisplay();
		rl_done = 1;
		write(STDERR_FILENO, "Quit: ", 6);
		ft_putnbr_fd(signum, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		return ;
	}
}

void	setup_read_interrupter()
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
}

void	setup_shell_quit()
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGQUIT, sigquit_handler);
}
