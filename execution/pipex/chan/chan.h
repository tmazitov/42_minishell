/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:02:20 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 18:16:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAN_H
# define CHAN_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../../../libft/get_next_line.h"

typedef struct s_log_chan
{
	int	*side;
	int	side_count;
}		t_log_chan;

t_log_chan	*make_log_chan(void);
void		*free_log_chan(t_log_chan *chan);
int			close_write(t_log_chan *chan);
int			close_read(t_log_chan *chan);
int			set_write(t_log_chan *chan, int fd);
int			set_read(t_log_chan *chan, int fd);

#endif // !CHAN_H
