/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:51:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/25 17:13:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	fill_heredoc(t_log_chan *chan, char	*limiter);
static char	*make_limiter(char *temp);
static t_log_chan	*chan_by_last_heredoc(char **payload);

static int	fill_heredoc(t_log_chan *chan, char	*limiter)
{
	char	*buffer;

	buffer = NULL;
	setup_read_interrupter();
	printf("heredoc limiter '%s'\n", limiter);
	while (!buffer || ft_strncmp(buffer, limiter, ftt_strlen(buffer)))
	{
		if (buffer)
		{
			write(chan->side[1], buffer, ftt_strlen(buffer));
			free(buffer);
		}
		ft_printf("> ");
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			return (1);
	}
	close_write(chan);
	free(buffer);
	return (0);
}

static char	*make_limiter(char *temp)
{
	int			len;

	len = 0;
	while(temp[len] && temp[len] != ' ')
		len++;
	return (ft_substr(temp, 0, len));
}

static t_log_chan	*chan_by_last_heredoc(char **payload)
{
	char		*temp;
	char		*limiter;
	t_log_chan	*chan;

	signal(SIGINT, sigint_handler);

	chan = NULL;
	while (ftt_strnstr(*payload, "<<", ftt_strlen(*payload)))
	{
		if (chan)
			chan = free_log_chan(chan);
		if (!(temp = ftt_strnstr(*payload, "<<", ftt_strlen(*payload)) + 3))
			return (NULL);
		if (!(limiter = make_limiter(temp)))
			return (NULL);
		if (!(chan = make_log_chan()))
			return (free(limiter), NULL);
		if (fill_heredoc(chan, limiter) != 0)
			return (free(limiter), free_log_chan(chan));
		*payload = temp + ft_strlen(limiter);
		printf("heredoc new payload '%s'\n", *payload);
		if (**payload == ' ')
			payload++;
		free(limiter);
	}
	return (chan);
}

/// @brief Open each one heredoc and return a channel of the last one.
/// @param com_payload pointer to the user input
/// @return Channel of the last heredoc
t_log_chan *make_heredoc(char **com_payload)
{
	t_log_chan	*chan;
	char		*new_payload;
	char		*command;
	int			len;

	if (!*com_payload ||
		!ftt_strnstr(*com_payload, "<<", ft_strlen(*com_payload)))
		return (NULL);
	new_payload = *com_payload;
	chan = chan_by_last_heredoc(&new_payload);
	if (!chan)
		return (NULL);
	len = 0;
	command = *com_payload;
	while (command[len])
	{
		if (command[len] == '<' &&
			command[len+1] && command[len+1] == '<')
			break ;
		len++;
	}
	command = ft_substr(*com_payload, 0, len);
	if (!command)
		return (free_log_chan(chan));
	printf("command '%s'\n", command);
	if (*new_payload != '\0')
		new_payload = ftt_strjoin(command, new_payload);
	else
		new_payload = command; 
	if (!new_payload)
		return (free(command), free_log_chan(chan));
	printf("command '%s'\n", new_payload);
	free(*com_payload);
	*com_payload = new_payload;
	return (chan);
}
