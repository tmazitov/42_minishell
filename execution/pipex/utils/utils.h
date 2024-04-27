/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:10:47 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 19:05:37 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../../libft/ft_printf.h"
# include "../../../builtins/builtins.h"
# include "../../../libft/libft.h"

void	panic(char *message, int status);
void	*free_split(char **split_result);
char	*find_path(t_envlist **envlist);
char	*find_command_path(char *command_name, char *env_path);
char	**ftt_split(char const *str, char ch);
char	*ftt_strjoin(char const *str1, char const *str2);
char	*ftt_substr(char const *str, unsigned int start, size_t len);
size_t	ftt_strlen(const char *str);
char	*ftt_strnstr(const char *big, const char *little, size_t len);
#endif // UTILS_H
