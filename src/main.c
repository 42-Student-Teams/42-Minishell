/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/17 20:31:00 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int ac, char **av, char **env)
{
	t_tree	*root;
	t_shell	shell;

	(void)av;
	(void)env;
	root = NULL;
	ft_bzero((void *)&shell, 0);
	ft_bzero((void *)root, 0);
	ft_bzero((void *)&g_shell, 0);
	if (ac > 1)
	{
		printf("Too many arguments\n");
		return (1);
	}
	while (42)
	{
		shell.input = readline("Minishell$ ");
		if (shell.input == NULL)
			exit (0);
		if (shell.input[0] != '\0')
		{
			add_history(shell.input);
			if (ft_strcmp(shell.input, "exit") == 0)
				exit(0);
			if (test_builtins(shell.input) == 1)
			{
				printf("BUILTIN ERROR\n");
				exit (1);
			}
		}
	}
	return (0);
}
