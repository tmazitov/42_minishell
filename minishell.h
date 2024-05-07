/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:16:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/07 12:25:13 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./execution/includes/execution.h"
#include "./parsing/includes/parse.h"
#include "./libft/libft.h"
#include "./builtins/builtins.h"
#include <readline/readline.h>

char	*ft_cleaninput(char *str);
char	*ft_cleaninput_b(char *str);
void	run_minicmd(char *str, t_envlist **envlist, t_varlist **varlist);
void	ft_free_ast(t_astnodes *root);

void	rl_replce_line (const char *, int);

#endif // MINISHELL_H