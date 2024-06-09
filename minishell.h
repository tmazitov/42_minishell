/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:16:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 04:22:07 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./execution/includes/execution.h"
#include "./parsing/includes/parse.h"
#include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

char		*ft_cleaninput(char *str);
char		*ft_cleaninput_b(char *str);
int			run_one_command(char *user_input, t_envlist **envlist, t_varlist **varlist);
int 		run_single_command(char *user_input, t_envlist **envlist, t_varlist **varlist);

t_varlist	*prepare_var(t_varlist **var);
t_envlist	*prepare_env(t_envlist **env, char **envp);
char		*prepare_single_command(char *user_input);
char		*prepare_user_input();
void		graceful_finish(t_envlist **env, t_varlist **var);

bool		user_input_is_valid(char *user_input);
bool		is_sh_file(char *user_input);
bool		is_single_command(int argc, char **argv);
void		different_execute(char *user_input, t_envlist **envlist, t_varlist **varlist);
#endif // MINISHELL_H