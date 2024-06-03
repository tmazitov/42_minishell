/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:11:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/03 17:13:15 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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