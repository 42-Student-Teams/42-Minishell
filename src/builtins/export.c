/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:47 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 12:11:44 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_value(char *args, t_env *tmp, char *key)
{
	while (ft_strcmp(tmp->key, key))
			tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_substr(args, ft_strchr(args, '=')
			- args + 1, ft_strlen(args));
}

static void	print_error_msg(char *s)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static char	*check_valid(char *s, int i)
{
	int		len;
	char	*key;

	len = ft_strlen(s);
	key = s;
	while (s[++i] && i < len - 1)
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			print_error_msg(s);
			return (NULL);
		}
	}
	if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '+')
	{
		print_error_msg(s);
		return (NULL);
	}
	if (s[i] == '+')
	{
		key = ft_substr(s, 0, len - 1);
		free(s);
	}
	return (key);
}

static void	add_to_env(char *args, t_env **env_l, int *not_in)
{
	t_env	*tmp;
	char	*key;

	if (is_equal_in(args))
	{
		tmp = *env_l;
		key = ft_substr(args, 0, ft_strchr(args, '=') - args);
		key = check_valid(key, -1);
		if (key)
		{
			if (key_in_env(key, *env_l))
				change_value(args, tmp, key);
			else
			{
				*env_l = new_el(key);
				(*env_l)->next = tmp;
				tmp->prev = *env_l;
			}
		}
		free(key);
	}
	else
		++(*not_in);
}

int	my_export(char **args, t_env **env_l)
{
	int		i;
	int		not_in;
	t_env	*tmp;

	tmp = *env_l;
	not_in = 0;
	if (!args[1])
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
	i = 0;
	while (args[++i])
		add_to_env(args[i], env_l, &not_in);
	return (not_in);
}
