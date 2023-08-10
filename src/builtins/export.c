/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:47 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/11 01:25:58 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (1);
	}
	return (0);
}

static int	in_env(char *key, t_env *env_l)
{
	t_env	*tmp;

	tmp = env_l;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	change_value(char *args, t_env *tmp, char *key)
{
	while (ft_strcmp(tmp->key, key))
			tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_substr(args, ft_strchr(args, '=')
			- args + 1, ft_strlen(args));
}

static void	add_to_env(char **args, t_env **env_l, int *not_in)
{
	t_env	*tmp;
	char	*key;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (is_in(args[i]))
		{
			if (!(*env_l))
				*env_l = new_el(args[i++]);
			tmp = *env_l;
			key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			if (in_env(key, *env_l))
				change_value(args[i], tmp, key);
			else
			{
				*env_l = new_el(args[i]);
				(*env_l)->next = tmp;
			}
			free(key);
		}
		else
			++(*not_in);
	}
}

int	my_export(char **args, t_env **env_l)
{
	int		not_in;
	t_env	*tmp;

	tmp = *env_l;
	not_in = 0;
	if (!args[1])
	{
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	add_to_env(args, env_l, &not_in);
	return (not_in);
}
