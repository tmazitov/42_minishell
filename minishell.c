/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/08 12:52:23 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	int				status;
	t_astnodes		*root;
	t_envlist		*envlist;
	t_varlist		*varlist;

	// (void)argc;
	// (void)argv;
	envlist = ft_init_env(envp);
	varlist = ft_init_var();
	if (ft_strncmp("-c", argv[2], 3) == 0)
		run_minicmd(argv[1], &envlist, &varlist);
	setup_read_interrupter();
	setup_shell_quit();
	status_code(SET, 0);
	while (1)
	{
		str = readline("\033[1;32mminishell$\033[0m ");
		if (str)
			status_code(SET, 0);
		if (!str && status_code(GET, -1) == 130)
		{
			status_code(SET, 0);
			continue ;
		}
		if (!str)
			return (1);
		str = ft_cleaninput(str);
		while (ft_isspace(*str) > 0)
			str++;
		if (ft_strlen(str) > 0 && *str != '\0')
		{
			add_history(str);
			if (ft_checkshfile(str))
				ft_openshfile(str);
			else
			{
				root = parse_input(str);
				// ft_builtins(str, &envlist, &varlist);
				if (root)
				{
					status = execute(root, &envlist, &varlist);
					if (status >= 0)
						ft_printf("success execution : status code %d\n", \
							status);
					else if (status_code(GET, -1))
						ft_printf("success execution : status code %d\n", \
							status_code(GET, -1));
					else
						ft_printf("execution error : status code %d\n", \
							status);
				}
				ft_free_ast(root);
			}
			free(str);
		}
	}
	ft_free_env(&envlist);
	ft_free_var(&varlist);
	return (0);
}

void	run_minicmd(char *str, t_envlist **envlist, t_varlist **varlist)
{
	int				status;
	t_astnodes		*root;

	setup_read_interrupter();
	setup_shell_quit();
	status_code(SET, 0);
	str = ft_cleaninput_b(str);
	if (str)
		status_code(SET, 0);
	if (!str && status_code(GET, -1) == 130)
	{
		status_code(SET, 0);
		return ;
	}
	if (!str)
		return ;
	while (ft_isspace(*str) > 0)
		str++;
	if (ft_strlen(str) > 0 && *str != '\0')
	{
		add_history(str);
		if (ft_checkshfile(str))
			ft_openshfile(str);
		else
		{
			root = parse_input(str);
			// ft_builtins(str, envlist, varlist);
			if (root)
			{
				status = execute(root, envlist, varlist);
				if (status >= 0)
					ft_printf("success execution : status code %d\n", \
						status);
				else if (status_code(GET, -1))
					ft_printf("success execution : status code %d\n", \
						status_code(GET, -1));
				else
					ft_printf("execution error : status code %d\n", \
						status);
			}
			ft_free_ast(root);
		}
		free(str);
	}
	ft_free_env(envlist);
	ft_free_var(varlist);
	exit(EXIT_SUCCESS);
}

void	ft_free_ast(t_astnodes *root)
{
	t_astnodes	*prev;

	while (root != NULL)
	{
		free((root)->value);
		free((root)->left);
		prev = root;
		root = (root)->right;
		free(prev);
	}
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
