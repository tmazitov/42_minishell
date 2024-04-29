/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:51:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/29 21:09:01 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	fill_heredoc(t_log_chan *chan, char	*limiter);
static char	*make_limiter(char *temp);
static t_log_chan	*chan_by_last_heredoc(char **payload);

static int	fill_heredoc(t_log_chan *chan, char	*limiter)
{
	char	*buffer;

	buffer = readline("> ");
	while (buffer && ft_strncmp(buffer, limiter, ft_strlen(limiter))
			&& status_code(GET, -1) != STOP_HEREDOC)
	{
		write(chan->side[1], buffer, ft_strlen(buffer));
		write(chan->side[1], "\n", 1);
		free(buffer);
		buffer = readline("> ");
	}
	close_write(chan);
	free(buffer);
	if (status_code(GET, -1) == STOP_HEREDOC)
		return (1);
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

	chan = NULL;
	while (ftt_strnstr(*payload, "<<", ftt_strlen(*payload)))
	{
		status_code(SET, IN_HEREDOC);
		if (chan)
			chan = free_log_chan(chan);
		if (!(temp = ftt_strnstr(*payload, "<<", ftt_strlen(*payload)) + 3))
			return (NULL);
		if (!(limiter = make_limiter(temp)))
			return (NULL);
		if (!(chan = make_log_chan()))
			return (free(limiter), NULL);
		if (status_code(SET, fill_heredoc(chan, limiter)) != 0)
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
