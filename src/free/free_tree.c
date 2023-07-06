/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:50:38 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 19:55:17 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tree(t_tree *node)
{
    if (node == NULL)
        return ;
    // Free the left subtree
	if (node->left)
    {
		free_tree(node->left);
    	node->left = NULL;
	}
    // Free the right subtree
    if (node->right)
    {
		free_tree(node->right);
    	node->right = NULL;
	}
    // Free the command string
    if (node->cmd)
	{
		free(node->cmd);
    	node->cmd = NULL;
	}
    // Free the current node
    free(node);
	node = NULL;
}
