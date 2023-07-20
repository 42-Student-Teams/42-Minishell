/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:26:01 by bverdeci          #+#    #+#             */
/*   Updated: 2023/07/20 16:42:47 by lsaba-qu         ###   ########.fr       */
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
	{
		my_echo(args);
	}
	free_split(args);
	return (0);
}



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
