/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_prep.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:54 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/20 19:49:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_user_input(void)
{
	char	*str;
	char	*str_temp;
	char	*str_head;

	str_temp = NULL;
	str = readline("\033[1;32mminishell$\033[0m ");
	if (!str)
		return (NULL);
	str = ft_cleaninput(str);
	str_head = str;
	while (ft_isspace(*str) > 0)
		str++;
	if (*str == '\0')
		return (free(str_head), return_voidpointer());
	str_temp = ft_strdup(str);
	if (!str_temp)
		return (free(str_head), NULL);
	return (free(str_head), str_temp);
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

char	*return_voidpointer(void)
{
	char	*out;

	out = malloc(sizeof(char) * 1);
	ft_bzero(out, sizeof(char) * 1);
	return (out);
}
