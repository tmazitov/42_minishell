/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/08 20:59:53 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_astnodes	*parse_input(char *str)
{
	t_tokens	*token_input;
	t_tokens	*token_head;
	t_astnodes	*root;

	if (!str || !*str)
		return (NULL);
	token_input = NULL;
	token_input = token_out(str);
	if (token_input == NULL)
		return (NULL);
	root = NULL;
	token_head = token_input;
	if (ft_shellgrammar(token_input) && ft_checksyntax(token_input))
	{
		root = ft_parsetokens(&token_input);
		ft_print_tokens_test(token_head, root);
		if (root == NULL)
			return (ft_free_tokens(token_input), NULL);
	}
	ft_free_tokens(token_head);
	return (root);
}

t_tokens	*token_out(char *str)
{
	char		**str_split;
	t_tokens	*token_input;

	str_split = NULL;
	str_split = ft_splittoken(str);
	if (!str_split)
		return (NULL);
	str_split = str_token(str_split);
	if (str_split == NULL)
		return (free_pointer(str_split), NULL);
	token_input = tokenize_input(str_split);
	if (token_input == NULL)
		return (free_pointer(str_split), NULL);
	return (token_input);
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

void	ft_print_tokens_test(t_tokens *token_input, t_astnodes *root)
{
	print_tokens(token_input);
	ft_printf("\n----------------- PRINT AST ---------------\n");
	print_ast(root, 0);
	ft_printf("--------------------------------------------\n");
}
