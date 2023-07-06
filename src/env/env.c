/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:49:43 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 20:44:46 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_shell *shell, char **env)
{
	int i = 0;

	// Check if the env parameter is NULL
	if (env == NULL)
		return 1;

	// Iterate through the env array
	while (env[i])
	{
		// Create a new environment variable node
		t_env *new_env = malloc(sizeof(t_env));
		if (new_env == NULL)
			return 1;

		// Extract the key and value from the env string
		char *key = strtok(env[i], "=");
		char *value = strtok(NULL, "=");

		// Set the key and value for the new environment variable node
		new_env->key = ft_strdup(key);
		new_env->value = ft_strdup(value);
		new_env->next = NULL;

		// Insert the new node into the linked list
		if (shell->env == NULL)
		{
			// If the linked list is empty, set the new node as the head
			shell->env = new_env;
		}
		else
		{
			// If the linked list is not empty, find the last node and append the new node
			t_env *current = shell->env;
			while (current->next != NULL)
				current = current->next;
			current->next = new_env;
		}

		i++;
	}
}
