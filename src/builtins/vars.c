/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:40:19 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/05 19:18:03 by lsaba-qu         ###   ########.fr       */
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
//	printf("status: %s %p\n", tmp->value, &tmp->value);
}

static void	print_error_msg(char *s)
{
	ft_putstr_fd("bash: `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd("': command not found", STDERR_FILENO);
}

static char	*check_valid(char *s, int i)
{
	int		len;
	char	*key;

	len = ft_strlen(s);
	key = s;

	while (s[++i] && i < len - 1)
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '?')
		{
			print_error_msg(s);
			return (NULL);
		}
	}
	if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '+' && s[i] != '?')
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


static char	*key_in_env_var(char *key, t_env *env_l)
{
	t_env	*tmp;

	tmp = env_l;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	add_to_env_var(char *args, t_env **env_l)
{
	t_env	*tmp;
	char	*key;

	tmp = *env_l;
	key = ft_substr(args, 0, ft_strchr(args, '=') - args);
	key = check_valid(key, -1);
	if (key)
	{
		if (key_in_env_var(key, *env_l))
			change_value(args, tmp, key);
		else
		{
			*env_l = new_el(key);
			(*env_l)->value = ft_substr(args, ft_strchr(args, '=')
				- args + 1, ft_strlen(args));
			(*env_l)->next = tmp;
			if (tmp)
				tmp->prev = *env_l;
		}
		free(key);
		return (0);
	}
	return (1);
}

int	my_vars(char **args, t_env **env_l)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (add_to_env_var(args[i], env_l) == 1)
			return (127);
	}
	return (0);
}
