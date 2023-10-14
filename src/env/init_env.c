/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:49:43 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 18:34:23 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **env, t_global *g_shell)
{
	int	i;

	i = 0;
	g_shell->env_copy = ft_calloc(sizeof(char **), 1000);
	if (!g_shell->env_copy)
		return ;
	while (env[i])
	{
		g_shell->env_copy[i] = ft_strdup(env[i]);
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
	new->prev = NULL;
	return (new);
}

// crée la liste liste 

int	env_list(t_env **env_l, char **env_copy)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;

	i = 0;
	tmp = NULL;
	if (!env_copy[0])
		return (NO_ENV);
	*env_l = new_el(env_copy[i]);
	prev = NULL;
	while (env_copy[++i])
	{
		tmp = *env_l;
		while (tmp->next)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new_el(env_copy[i]);
		tmp->prev = prev;
		if (!(tmp->next))
			return (ERROR);
	}
	return (0);
}

void	fake_env(t_env **env_l)
{
	*env_l = new_el("PATH");
}
