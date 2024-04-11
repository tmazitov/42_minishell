/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:08:40 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/08 22:58:47 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printstr(char **str_split)
{
	int	word_count;
	int	index;
	int	count;

	word_count = strsplit_count(str_split);
	index = 1;
	while (index <= word_count)
	{
		ft_printf("o--------------------");
		index++;
	}
	ft_printf("o\n");
	ft_printf("|");
	index = 1;
	while (index <= word_count)
	{
		ft_printf("       PARAM %d      |", index);
		index++;
	}
	ft_printf("\n");
	index = 1;
	while (index <= word_count)
	{
		ft_printf("o--------------------");
		index++;
	}
	ft_printf("o\n");
	ft_printf("|");
	index = 0;
	while (*str_split)
	{
		ft_printf("%19s |", *str_split);
		index++;
		str_split++;
	}
	while (index < word_count)
	{
		count = 0;
		while (count < 8)
			ft_printf(" ");
		ft_printf("|");
		index++;
	}
	ft_printf("\n");
	index = 1;
	while (index <= word_count)
	{
		ft_printf("o--------------------", index);
		index++;
	}
	ft_printf("o\n");
}

int	strsplit_count(char **str_split)
{
	int	count;

	count = 0;
	while (*str_split)
	{
		count++;
		str_split++;
	}
	return (count);
}
