/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:47 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/10 12:59:01 by bverdeci         ###   ########.fr       */
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

static void	change_value(char **args, t_env *tmp, char *key)
{
	while (ft_strcmp(tmp->key, key))
			tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_substr(args[1], ft_strchr(args[1], '=')
			- args[1] + 1, ft_strlen(args[1]));
	free(key);
}

int	my_export(char **args, t_env **env_l)
{
	int		len;
	t_env	*tmp;
	char	*key;

	len = strtab_len(args);
	if (len > 2 || len < 2 || !is_in(args[1]))
		return (0);
	if (!(*env_l))
	{
		*env_l = new_el(args[1]);
		if (!(*env_l))
			return (1);
		return (0);
	}
	tmp = *env_l;
	key = ft_substr(args[1], 0, ft_strchr(args[1], '=') - args[1]);
	if (in_env(key, *env_l))
	{
		change_value(args, tmp, key);
		return (0);
	}
	free(key);
	*env_l = new_el(args[1]);
	(*env_l)->next = tmp;
	return (0);
}
