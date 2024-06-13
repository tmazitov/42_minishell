/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toktoast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:55:46 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 13:57:23 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief create an AST from the t_tokens (token list) with recursive descent
/// parsing.
/// @brief The recursive descent happens at the next command (or the right
/// side) from the PIPE
/// @param tokens t_tokens list
/// @return abstract syntax tree
t_astnodes	*ft_parsetokens(t_tokens **tokens)
{
	t_astnodes	*command;
	t_astnodes	*node;
	t_astnodes	*nextcommand;
	char		*operator;

	command = parse_command(tokens);
	if (command == NULL)
		return (NULL);
	if ((*tokens != NULL) && ((*tokens)->type == PIPE))
	{
		operator = ft_strdup((*tokens)->value);
		(*tokens) = (*tokens)->next;
		nextcommand = ft_parsetokens(tokens);
		node = (t_astnodes *)malloc(sizeof(t_astnodes));
		if (node == NULL)
			return (NULL);
		node->value = operator;
		node->left = command;
		node->right = nextcommand;
		return (node);
	}
	else
		return (command);
}

/// @brief merge strings from the left side of the current PIPE and set
/// the node->value equal to the merged string/
/// @param tokens token list
/// @return abstract syntax tree node
t_astnodes	*parse_command(t_tokens **tokens)
{
	t_astnodes	*node;

	if ((*tokens) == NULL)
		return (NULL);
	node = (t_astnodes *)malloc(sizeof(t_astnodes));
	if (node == NULL)
		return (NULL);
	if ((*tokens != NULL) && (*tokens)->type != PIPE)
	{
		node->value = NULL;
		while ((*tokens != NULL) && (*tokens)->type != PIPE)
		{
			if ((node->value) && ft_strlen(node->value) > 0)
				node->value = merge_string(node->value, (*tokens)->value);
			else
				node->value = ft_strdup((*tokens)->value);
			(*tokens) = (*tokens)->next;
		}
	}
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/// @brief merge two strings into one
/// @param s1 string 1
/// @param s2 string 2
/// @return merged string
char	*merge_string(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;
	size_t	index;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!out)
		return (NULL);
	index = 0;
	while (index < len1)
	{
		out[index] = s1[index];
		index++;
	}
	out[index++] = ' ';
	while (index < (len1 + len2 + 1))
	{
		out[index] = s2[index - len1 - 1];
		index++;
	}
	free(s1);
	out[index] = '\0';
	return (out);
}

int	ft_modeoperator(char c, int mode)
{
	if ((c == '\'' || c == '\"') && mode == 1)
		mode = 0;
	else if ((c == '\'' || c == '\"') && mode == 0)
		mode = 1;
	return (mode);
}

void	print_ast(t_astnodes *rootnode, int depth)
{
	int	i;

	if (rootnode == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		ft_printf(" ");
		i++;
	}
	ft_printf("%s\n", rootnode->value);
	print_ast(rootnode->left, depth + 2);
	print_ast(rootnode->right, depth + 4);
}
