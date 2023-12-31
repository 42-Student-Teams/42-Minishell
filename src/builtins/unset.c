/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:51 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 18:18:17 by bverdeci         ###   ########.fr       */
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

static int	check_valid_unset(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			printf("bash: unset: `%s': not a valid identifier\n", s);
			return (0);
		}
	}
	return (1);
}

int	my_unset(t_env **env_l, char **args, int i)
{
	t_env	*tmp;
	int		found;
	int		not_in;

	not_in = 0;
	while (args[++i])
	{
		tmp = *env_l;
		found = 0;
		if (check_valid_unset(args[i]))
		{
			while (tmp)
			{
				if (ft_strcmp(tmp->key, args[i]) == 0)
				{
					delete_node(tmp, env_l, &found);
					break ;
				}
				tmp = tmp->next;
			}
			if (found == 0)
				++not_in;
		}
	}
	return (g_status = not_in);
}
