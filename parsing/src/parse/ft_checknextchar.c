/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checknextchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:58:59 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/08 18:16:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief checks the next character if redir operator
/// @param c input string
/// @param index index of the operator character
/// @return return the number from the start index to the end of the redir 
/// operator
int	ft_checknextchar(char *c, int index)
{
	if (ft_strncmp(&c[index], DLESSDASH, 3) == 0)
		return (2);
	else if (c[index] == c[index + 1])
		return (1);
	else if (ft_strncmp(&c[index], LESSAND, 2) == 0)
		return (1);
	else if (ft_strncmp(&c[index], GREATAND, 2) == 0)
		return (1);
	else if (ft_strncmp(&c[index], LESSGREAT, 2) == 0)
		return (1);
	else if (ft_strncmp(&c[index], CLOBBER, 2) == 0)
		return (1);
	else
		return (0);
}

int	ft_checknextcharb(char *c, int index)
{
	if (c[index] == '{')
		return (1);
	else if (c[index] == '}')
		return (1);
	else if (c[index] == '(')
		return (1);
	else if (c[index] == ')')
		return (1);
	else
		return (0);
}

int	ft_checknextcharc(char *c, int index)
{
	if (ft_strncmp(&c[index], RBRACE, 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], LBRACE, 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], LPARAN, 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], RPARAN, 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], D_SIGN, 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], "\'", 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], "\"", 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], ">", 1) == 0)
		return (1);
	else if (ft_strncmp(&c[index], "<", 1) == 0)
		return (1);
	else
		return (0);
}
