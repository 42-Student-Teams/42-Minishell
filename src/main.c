/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42l>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/03 18:10:24 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/09/28 21:32:23 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* toujours utile pour debug
while (cmds)
{
	printf("CMD : %s\n", cmds->cmd);
	i = -1;
	printf("ARGS : \n");
	while (cmds->args[++i])
		printf("[%d] %s \n", i, cmds->args[i]);
	cmds = cmds->next;
}
*/

/*
** Volatile eviter que le preprocesseur optimise la variable
** (pour les signaux)
*/


void	init_shell(t_shell *shell, t_global *g_shell, char **env)
{	
	ft_bzero((void *)&shell, 0);
	copy_env(env, g_shell);
	g_shell->env_l = NULL;
	g_shell->vars = NULL;
	if (env_list(&g_shell->env_l, g_shell->env_copy) == 1)
	{
		ft_putendl_fd("env liste error", STDERR_FILENO);
		exit(1);
	}
	init_termios(1);
}

//void printTokens(t_token *head) {
//    t_token *current = head;
//
//    while (current != NULL) {
//        printf("Token str: %s\n", current->str);
//        current = current->next;
//    }
//}

void	prepare_cmd(t_shell *shell, t_global *g_shell)
{
	t_token		*tokens;
	t_parser	*cmds;
	int			i;

	tokens = NULL;
	cmds = NULL;
	i = 0;
	while (shell->input[i])
		i += lexer(g_shell, &tokens, shell->input, i);
	parser(&cmds, tokens, g_shell);
	execution(&cmds, g_shell);
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
			prepare_cmd(&shell, g_shell);
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
