/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:51 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/13 23:00:47 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env *tmp, t_env **env_l, int *found)
{
	if (tmp->prev != NULL && tmp->next != NULL)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if (tmp->prev == NULL && tmp->next != NULL)
	{
		*env_l = tmp->next;
		(*env_l)->prev = NULL;
	}
	else if (tmp->prev != NULL && tmp->next == NULL)
		tmp->prev->next = NULL;
	else
		*env_l = NULL;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	*found = 1;
}

int	my_unset(t_env **env_l, char **args)
{
	t_env	*tmp;
	int		found;
	int		not_in;
	int		i;

	not_in = 0;
	i = 0;
	while (args[++i])
	{
		tmp = *env_l;
		found = 0;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, args[i]) == 0)
			{
				delete_node(tmp, env_l, &found);
				break ;
			}
			else
				tmp = tmp->next;
		}
		if (found == 0)
			++not_in;
	}
	return (not_in);
}
