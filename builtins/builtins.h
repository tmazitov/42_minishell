/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:51 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINTS_H
# define BUILTINTS_H

# include "../parsing/libft/libft.h"
# include "../parsing/includes/parse.h"

void	ft_echo(char *str);
void	ft_printparams(char **cmd_split);
void	ft_printsquotes(char *str);
void	ft_printexpansion(char *str, int index);
void	ft_printdquotes(char *str);
bool    ft_checkvarname(char *varname);
char    *ft_getvarname(char *str, int index);
#endif //BUILTINTS_H

//$0 – The name of the Bash script.
// $1 to $9 – The first 9 arguments to the Bash script.
// $# – The number of arguments supplied to the Bash script.
// $@ – All the arguments supplied to the Bash script.
// $? – The exit status of the last command executed.