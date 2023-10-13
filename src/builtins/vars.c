/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:40:19 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/13 23:11:47 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_value(char *args, t_env *tmp, char *key)
{
	while (ft_strcmp(tmp->key, key))
			tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_substr(args, ft_strchr(args, '=')
			- args + 1, ft_strlen(args));
}

static void	print_error_msg(char *s)
{
	ft_putstr_fd("bash: `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd("': command not found", STDERR_FILENO);
}

static char	*process_plus_case(char *key, int len, char *s)
{
	key = ft_substr(s, 0, len - 1);
	free(s);
	return (key);
}

char	*check_valid(char *s, int i)
{
	int		len;
	char	*key;

	len = ft_strlen(s);
	key = s;
	while (s[++i] && i < len - 1)
	{
		if (!ft_isalpha(s[i])
			&& !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '?')
		{
			print_error_msg(s);
			return (NULL);
		}
	}
	if (!ft_isalpha(s[i])
		&& !ft_isdigit(s[i]) && s[i] != '_' && s[i] != '+' && s[i] != '?')
	{
		print_error_msg(s);
		return (NULL);
	}
	if (s[i] == '+')
		key = process_plus_case(key, len, s);
	return (key);
}

char	*key_in_env_var(char *key, t_env *env_l)
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
