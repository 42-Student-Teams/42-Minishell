/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:27:12 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/13 22:55:18 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal_in(char *s)
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

int	key_in_env(char *key, t_env *env_l)
{
	t_env	*tmp;
	char	keyandenv[10];
	char	*str_status;

	tmp = env_l;
	ft_strcpy(keyandenv, "?=");
	str_status = ft_itoa((int)g_status);
	ft_strcpy(keyandenv + 2, str_status);
	free(str_status);
	add_to_env_var(keyandenv, &env_l);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
