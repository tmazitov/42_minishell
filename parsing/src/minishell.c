/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 12:55:05 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			parse_input(str);
		}
	}
	return (0);
}

void	parse_input(char *str)
{
	char		**str_split;
	t_tokens	*token_input;
	t_astnodes	*root;

	str_split = ft_splittoken(str);
	if (!str_split)
		return ;
	str_split = str_token(str_split);
	token_input = tokenize_input(str_split);
	if (ft_shellgrammar(token_input) && ft_checksyntax(token_input))
	{
		print_tokens(token_input);
		root = ft_parsetokens(&token_input);
		ft_printf("\n----------------- PRINT AST ---------------\n");
		print_ast(root, 0);
		ft_printf("--------------------------------------------\n");
	}
	free(str);
	free_pointer(str_split);
}

void	ft_freesplit(char **str)
{
	int	len;
	int	index;

	len = strsplit_size(str);
	index = 0;
	while (index < len)
	{
		free(str[index]);
		index++;
	}
	free(str);
}

int	strsplit_size(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
