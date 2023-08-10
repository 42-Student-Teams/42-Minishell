/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:49:43 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/10 13:00:06 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **env)
{
	int	i;

	i = 0;
	g_shell.env_copy = ft_calloc(sizeof(char **), 1000);
	while (env[i])
	{
		g_shell.env_copy[i] = ft_strdup(env[i]);
		i++;
	}
}

// crée un élément de la liste

t_env	*new_el(char *key_value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_substr(key_value, 0, ft_strchr(key_value, '=') - key_value);
	new->value = ft_substr(key_value, ft_strchr(key_value, '=')
			- key_value + 1, ft_strlen(key_value));
	new->next = NULL;
	return (new);
}

// crée la liste liste 

int	env_list(t_env **env_l, char **env_copy)
{
	int		i;
	t_env	*tmp;

	i = 0;
	*env_l = new_el(env_copy[i]);
	while (env_copy[++i] && *env_l)
	{
		tmp = *env_l;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_el(env_copy[i]);
		if (!(tmp->next))
			return (1);
	}
	return (0);
}
