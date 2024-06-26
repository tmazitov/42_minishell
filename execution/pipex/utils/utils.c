/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:04:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 19:39:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ftt_strlen(const char *str)
{
	int	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

void	panic(char *message, int status)
{
	if (message)
	{
		ft_printf("pipex: ");
		ft_printf(message);
	}
	exit(status);
}

char	*ftt_strjoin(char const *str1, char const *str2)
{
	char	*result;
	int		counter;

	counter = 0;
	if (!str1 || !str2 || (ftt_strlen(str1) + ftt_strlen(str2) >= INT_MAX))
		return (NULL);
	result = malloc(sizeof(char) * (ftt_strlen(str1) + ftt_strlen(str2) + 1));
	if (!result)
		return (NULL);
	while (*str1)
		result[counter++] = *str1++;
	while (*str2)
		result[counter++] = *str2++;
	result[counter] = '\0';
	return (result);
}

char	*ftt_strdup(const char *str)
{
	int		i;
	int		len;
	char	*new_str;

	len = 0;
	while (str[len])
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new_str))
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ftt_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	counter;
	size_t	str_len;
	size_t	sub_len;

	if (!str)
		return (NULL);
	str_len = ftt_strlen(str);
	if (start + len <= str_len)
		sub_len = len;
	else if (str_len - 1 < start)
		sub_len = 0;
	else
		sub_len = str_len - start;
	sub_str = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	counter = 0;
	while (counter < sub_len && str[counter + start])
	{
		sub_str[counter] = str[counter + start];
		counter++;
	}
	sub_str[sub_len] = '\0';
	return (sub_str);
}
