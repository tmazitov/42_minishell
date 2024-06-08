/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:50:55 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 03:50:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*heredoc_temp_filepath(void)
{
	static int	temp_file_num;
	char		*num_str;
	char		*filename;

	temp_file_num += 1;
	num_str = ft_itoa(temp_file_num);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/var/tmp/heredoc_", num_str);
	if (!filename)
		return (NULL);
	free(num_str);
	return (filename);
}
