/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 19:16:45 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/includes/parse.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			if (ft_checkshfile(str))
				ft_openshfile(str);
			free(str);
		}
	}
	return (0);
}
