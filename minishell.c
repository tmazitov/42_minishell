/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/04 15:41:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int				err_status;
	char			*user_input;
	t_envlist		*envlist;
	t_varlist		*varlist;

	if (!(envlist = ft_init_env(envp))
		|| !(varlist = ft_init_var()))
		return (ft_free_env(&envlist), 1);
	if (is_single_command(argc, argv))
		return (run_single_command(argv[2], &envlist, &varlist));
	setup_read_interrupter();
	setup_shell_quit();
	status_code(SET, 0);
	while (1)
	{
		if (!(user_input = prepare_user_input()))
			break ;
		err_status = run_one_command(user_input, &envlist, &varlist);
		if (err_status)
			break ;
	}
	ft_free_env(&envlist);
	ft_free_var(&varlist);
	rl_clear_history();
	return (0);
}

int 	run_single_command(char *user_input, t_envlist **envlist, t_varlist **varlist)
{
	user_input = prepare_single_command(user_input);
	if ((!user_input && status_code(GET, -1) == 130 )|| (!user_input_is_valid(user_input))) 
	{
		if (user_input)
			free(user_input);
		status_code(SET, 0);
		return (0);
	}
	if (!user_input)
		return (1);
	different_execute(user_input, envlist, varlist);
	ft_free_env(envlist);
	ft_free_var(varlist);
	return (0);
}	

int		run_one_command(char *user_input, t_envlist **envlist, t_varlist **varlist)
{
	if ((!user_input && status_code(GET, -1) == 130 )|| (!user_input_is_valid(user_input))) 
	{
		status_code(SET, 0);
		return (0);
	}
	if (!user_input)
		return (1);
	add_history(user_input);
	different_execute(user_input, envlist, varlist);
	return (0);
}

char	*ft_cleaninput_b(char *str)
{
	int		len;
	char	*out;

	len = 0;
	out = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!out)
		return (NULL);
	ft_bzero(out, ft_strlen(str) + 1);
	while (str[len] != '\0' && str[len] != '\n')
	{
		out[len] = str[len];
		len++;
	}
	out[len] = '\0';
	// free(str);
	return (out);
}

char	*ft_cleaninput(char *str)
{
	size_t	len;
	char	*out;

	len = 0;
	out = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!out)
		return (NULL);
	ft_bzero(out, ft_strlen(str) + 1);
	while (str[len] != '\0' && str[len] != '\n')
	{
		out[len] = str[len];
		len++;
	}
	out[len] = '\0';
	free(str);
	return (out);
}
