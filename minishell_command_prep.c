/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_prep.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/18 17:59:32 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_user_input(void)
{
	char	*str;

	str = readline("\033[1;32mminishell$\033[0m ");
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
