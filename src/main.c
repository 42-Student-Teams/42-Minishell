/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/13 13:30:55 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int ac, char **av, char **env)
{
	t_tree	*root;
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	root = NULL;
	ft_bzero((void *)&shell, 0);
	ft_bzero((void *)root, 0);
	ft_bzero((void *)&g_shell, 0);
	(void) env;
	while (42)
	{
		shell.input = readline("Minishell$ ");
		if (shell.input)
			add_history(shell.input);
		else
			exit (0);
		if (ft_strcmp(shell.input, "exit") == 0)
			exit(0);
		if (test_builtins(shell.input) == 1)
		{
			printf("BUILTIN ERROR\n");
			exit (1);
		}
	}
	return (0);
}
