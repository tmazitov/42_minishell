/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/13 14:26:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_astnodes	*parse_input(char *str)
{
	char		**str_split;
	t_tokens	*token_input;
	t_astnodes	*root;

	if (!str)
		return (NULL);
	str_split = ft_splittoken(str);
	if (!str_split)
		return (NULL);
	root = NULL;
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
	free_pointer(str_split);
	return (root);
}
