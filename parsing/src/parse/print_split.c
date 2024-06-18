/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:52:00 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/18 19:50:53 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	print_split(char **str_split)
{
	int	count;

	count = 0;
	ft_printf("print_split\n");
	while (str_split[count])
	{
		ft_printf("|%s|\n", str_split[count]);
		count++;
	}
}
