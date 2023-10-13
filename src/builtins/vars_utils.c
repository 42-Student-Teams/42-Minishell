/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:40:19 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/13 23:08:48 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
