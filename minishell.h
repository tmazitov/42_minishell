/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:16:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/30 20:51:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./execution/includes/execution.h"
#include "./parsing/includes/parse.h"
#include "./libft/libft.h"
#include "./builtins/builtins.h"

char	*ft_cleaninput(char *str);
char	*ft_cleaninput_b(char *str);
void	run_minicmd(char *str, t_envlist **envlist, t_varlist **varlist);
void	ft_free_ast(t_astnodes *root);

#endif // MINISHELL_H