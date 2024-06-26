/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:56:10 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:24:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	char			*c;
	long long int	out;
	long long int	tent;
	int				sign;

	tent = 0;
	out = 0;
	sign = 1;
	c = (char *)(str);
	while ((*c >= 9 && *c <= 13) || *c == 32)
		c++;
	if ((*c == '-') || (*c == '+'))
		if (*c++ == '-')
			sign = -1;
	while (ft_isdigit(*c))
	{
		tent = (tent * 10) + (sign * (*c++ - '0'));
		if (tent > out && (sign < 0))
			return (0);
		else if (tent < out && sign > 0)
			return (-1);
		out = tent;
	}
	return ((out));
}
