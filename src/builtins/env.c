/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:42 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/16 11:47:58 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(char **args)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], " ") != 0)
		{
			ft_putendl_fd("env error", STDERR_FILENO);
			return (1);
		}
	}
	tmp = g_shell.env_l;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
