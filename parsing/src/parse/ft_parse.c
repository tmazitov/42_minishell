/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/21 17:15:41 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_astnodes	*parse_input(char *str)
{
	char		**str_split;
	t_tokens	*token_input;
	t_tokens	*token_head;
	t_astnodes	*root;

	if (!str || !*str)
		return (NULL);
	token_input = NULL;
	str_split = ft_splittoken(str);
	if (!str_split)
		return (NULL);
	str_split = str_token(str_split);
	token_input = tokenize_input(str_split);
	root = NULL;
	token_head = token_input;
	if (ft_shellgrammar(token_input) && ft_checksyntax(token_input))
	{
		print_tokens(token_input);
		root = ft_parsetokens(&token_input);
		ft_printf("\n----------------- PRINT AST ---------------\n");
		print_ast(root, 0);
		ft_printf("--------------------------------------------\n");
	}
	ft_free_tokens(token_head);
	free_pointer(str_split);
	return (root);
}

void	ft_free_tokens(t_tokens *tokens)
{
	t_tokens	*prev;

	while (tokens != NULL)
	{
		free(tokens->value);
		prev = tokens;
		tokens = tokens->next;
		free(prev);
	}
	free(tokens);
}