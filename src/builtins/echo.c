/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 19:42:07 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(char **args)
{
	int		i;
	char	*option;

	i = 1;
	option = NULL;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
			option = args[1];
			i = 2;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
