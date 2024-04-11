/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:48:59 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:52:07 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	parse_input(char *str)
{
	char		**str_split;
	t_tokens	*token_input;
	t_astnodes	*root;

	if (!str)
		return ;
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
	free_pointer(str_split);
}
