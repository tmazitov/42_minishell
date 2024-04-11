/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toktoast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:55:46 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 17:59:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_astnodes	*ft_parsetokens(t_tokens **tokens)
{
	t_astnodes	*command;
	t_astnodes	*node;
	t_astnodes	*nextcommand;
	char		*operator;

	command = parse_command(tokens);
	if ((*tokens != NULL) && ((*tokens)->type == PIPE))
	{
		operator = ft_strdup((*tokens)->value);
		(*tokens) = (*tokens)->next;
		nextcommand = ft_parsetokens(tokens);
		node = (t_astnodes *)malloc(sizeof(t_astnodes));
		node->value = operator;
		node->left = command;
		node->right = nextcommand;
		return (node);
	}
	else
		return (command);
}

t_astnodes	*parse_command(t_tokens **tokens)
{
	t_astnodes	*node;

	if ((*tokens) == NULL)
		return (NULL);
	node = (t_astnodes *)malloc(sizeof(t_astnodes));
	if ((*tokens != NULL) && (*tokens)->type != PIPE)
	{
		node->value = ft_strdup("");
		while ((*tokens != NULL) && (*tokens)->type != PIPE)
		{
			if (ft_strlen(node->value) > 0)
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
