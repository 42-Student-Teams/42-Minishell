/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:26:01 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/06 11:43:04 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_builtins(char *input)
{
	char	**args;
	char	*cmd;

	if (input[0] == ' ')
		return (0);
	args = ft_split(input, ' ');
	if (args == NULL)
		return (0);
	cmd = args[0];
	if (ft_strcmp(cmd, "cd") == 0)
	{
		if (my_cd(args) == 1)
			return (1);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
		my_echo(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		my_pwd();
	free_split(args);
	return (0);
}