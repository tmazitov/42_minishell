/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:16:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/19 17:58:45 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./execution/includes/execution.h"
# include "./parsing/includes/parse.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

char		*ft_cleaninput(char *str);
char		*ft_cleaninput_b(char *str);
int			run_one_command(char *user_input, t_envlist **envlist, \
			t_varlist **varlist);
int			run_single_command(char *user_input, t_envlist **envlist, \
			t_varlist **varlist);

t_varlist	*prepare_var(t_varlist **var);
t_envlist	*prepare_env(t_envlist **env, t_varlist **varlist, char **envp);
char		*prepare_single_command(char *user_input);
char		*prepare_user_input(void);
void		graceful_finish(t_envlist **env, t_varlist **var);

char		*prepare_single_command(char *user_input);
char		*prepare_user_input(void);

bool		user_input_is_valid(char *user_input);
bool		is_sh_file(char *user_input);
bool		is_single_command(int argc, char **argv);
void		different_execute(char *user_input, t_envlist **envlist, \
			t_varlist **varlist);
void		ft_checkdollar(t_astnodes **rootnode, t_builtin_info *info);
char		*ft_expanddollar(char *str, t_builtin_info *info);
char		*ft_expanddollar_b(char *out, int *count);
int			ft_expanddollar_cond(char c);
char		*ft_expanddollar_a(char *out, int *count);
char		*ft_expanddollar_c(char *str, char *out, int *count, \
			t_builtin_info *info);
char		*ft_mergedollar_a(char *str, char *out, int count);

t_astnodes	*ft_setroot(t_astnodes **rootnode, t_envlist *envlist, \
			t_varlist *varlist);
char		*ft_mergedollar_b(char	*varname, char *out, t_envlist *envlist, \
			t_varlist *varlist);
int			ft_selectmode(char c, char mode);
char		*ft_cleanvalue(char *str);
char		*return_voidpointer(void);
#endif // MINISHELL_H