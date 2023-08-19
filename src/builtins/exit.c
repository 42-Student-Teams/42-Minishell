/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:13:35 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/19 12:42:51 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

int	my_exit(char **args)
{
	int	exit_code;

	if (args[1])
	{
		if (is_number(args[1]))
		{
			if (args[2])
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
				return (1);
			}
			exit_code = ft_atoi(args[1]);
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(exit_code);
		}
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
	return (0);
}
