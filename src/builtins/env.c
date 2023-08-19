/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:42 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 16:12:26 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(char **args, t_global *g_shell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], " ") != 0)
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (127);
		}
	}
	tmp = g_shell->env_l;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
