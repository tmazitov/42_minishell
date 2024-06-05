/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_prep.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/05 19:20:04 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_user_input() 
{
	char	*str;

	str = readline("\033[1;32mminishell$\033[0m ");
	// if (str)
	// 	status_code(SET, 0);
	if (!str)
		return (NULL);
	str = ft_cleaninput(str);
	while (ft_isspace(*str) > 0)
		str++;
	return (str);
}

char	*prepare_single_command(char *user_input) 
{

	user_input = ft_cleaninput_b(user_input);
	// if (user_input)
	// 	status_code(SET, 0);
	if (!user_input && status_code(GET, -1) == 130)
	{
		status_code(SET, 0);
		return (NULL);
	}
	if (!user_input)
		return (NULL);
	while (ft_isspace(*user_input) > 0)
		user_input++;
	return (user_input);
}