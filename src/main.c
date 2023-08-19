/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 19:54:41 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, t_global *g_shell, char **env)
{	
	ft_bzero((void *)&shell, 0);
	copy_env(env, g_shell);
	g_shell->env_l = NULL;
	if (env_list(&g_shell->env_l, g_shell->env_copy) == 1)
	{
		ft_putendl_fd("env liste error", STDERR_FILENO);
		exit(1);
	}
	init_termios();
}

void	prepare_cmd(t_shell *shell)
{
	t_token *tokens;
	t_token *first;
	int		i;

	i = 0;
	tokens = NULL;
	while (shell->input && shell->input[i])
		i += lexer(&tokens, shell->input, i);

	(void)first;
	// first = (t_token *)ft_lst_get((t_list *)tokens, 0);
	// if (first && first->type == E_PIPE)
	// {
	// 	printf("PIPE ERROR\n");
	// 	exit(1);
	// }
}

void	init_loop(t_shell shell, t_global *g_shell)
{
	while (42)
	{
		shell.input = readline("Minishell$ ");
		if (!shell.input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		if (shell.input[0] != '\0')
		{
			if (ft_strlen(shell.input) != 0)
				add_history(shell.input);
			prepare_cmd(&shell);
			if (builtins(shell.input, g_shell) == 1)
			{
				printf("BUILTIN ERROR\n");
				exit (1);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		shell;
	t_global	g_shell;

	(void)av;
	(void)ac;
	if (isatty(0) && isatty(2))
		rl_outstream = stderr;
	ft_bzero((void *)&g_shell, 0);
	init_shell(&shell, &g_shell, env);
	init_loop(shell, &g_shell);
	return (0);
}
