/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_btree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 23:37:32 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 16:49:51 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_btree(t_node *node)
{
	if (node == NULL)
		return;

	// Recursively free the left and right subtrees
	free_btree(node->left);
	free_btree(node->right);

	// Free the members of the current node
	free(node->data);
	free(node->type);
	ft_free_pp((void **)node->cmd);

	// Free the current node itself
	free(node);
}
