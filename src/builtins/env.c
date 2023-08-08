/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:42 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/07 11:10:01 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(char **args)
{
	int i;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], " ") != 0)
		{
			ft_putendl_fd("env error", 2);
			return (1);
		}
	}
	i  = -1;
	while (g_shell.env_copy[++i])
		printf("%s\n", g_shell.env_copy[i]);
	return (0);
}	