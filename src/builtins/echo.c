/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/06 10:31:17 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_echo(char **args)
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
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
}
