/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/08 13:32:49 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	ft_bzero((void *)&shell, 0);
	ft_bzero((void *)&g_shell, 0);
	//copy env dans la variable globale accessible partout
	copy_env(env);
	// catch les signaux et cache le ^C, ^/ ,^D etc	
	init_termios();
	// init_env(&shell);
}

void	init_loop(t_shell shell)
{
	while (42)
	{
		shell.input = readline("Minishell$ ");
		if (!shell.input)
			exit(0);
		if (shell.input[0] != '\0')
		{
			if (ft_strlen(shell.input) != 0)
				add_history(shell.input);
			if (ft_strncmp(shell.input, "exit", 4) == 0)
				exit(0);
			if (test_builtins(shell.input) == 1)
			{
				printf("BUILTIN ERROR\n");
				exit (1);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	(void)ac;
	//check si on est dans un terminal
	if (isatty(0) && isatty(2))
		rl_outstream = stderr;
	init_shell(&shell, env);
	init_loop(shell);
	return (0);
}
