/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:11:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 05:52:01 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_free_ast(t_astnodes *root)
{
	ft_free_ast_temp(root);
	free(root);
}

void	ft_free_ast_temp(t_astnodes *rootnode)
{
	if (rootnode == NULL)
		return ;
	free(rootnode->value);
	ft_free_ast_temp(rootnode->left);
	ft_free_ast_temp(rootnode->right);
	free(rootnode->left);
	free(rootnode->right);
}
