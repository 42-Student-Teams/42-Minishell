/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/07 12:48:22 by lsaba-qu         ###   ########.fr       */
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
		{
			printf("Exit\n");
			exit(0);
		}
	}
	return (0);
}
