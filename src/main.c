/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42l>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/12 15:12:08 by lsaba-qu         ###   ########.fr       */
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

void	init_shell(t_shell *shell, t_global *g_shell, char **env)
{
	int res;

	ft_bzero((void *)&shell, 0);
	copy_env(env, g_shell);
	g_shell->env_l = NULL;
	g_shell->vars = NULL;
	g_status = 0;
	res = env_list(&g_shell->env_l, g_shell->env_copy);
	if (res == ERROR)
	{
		ft_putendl_fd("Minishell: Launch with an environment", STDERR_FILENO);
		exit(1);
	}
	if (res == NO_ENV)
		fake_env(&g_shell->env_l);

	init_termios(1);
	assign_g_status(g_shell);
}

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

//void	print_vars(t_env *vars)
//{
//	t_env	*tmp;
//
//	tmp = vars;
//	while (tmp)
//	{
//		printf("%s=%s\n", tmp->key, tmp->value);
//
//		tmp = tmp->next;
//	}
//}

void	assign_g_status(t_global *g_shell)
{
	char keyandenv[10];
	char *str_status;

	ft_strcpy(keyandenv, "?=");
	str_status = ft_itoa((int)g_status);
	ft_strcpy(keyandenv + 2, str_status);
	free(str_status);
	add_to_env_var(keyandenv, &g_shell->vars);
}

void	init_loop(t_shell shell, t_global *g_shell)
{
	assign_g_status(g_shell);
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
			assign_g_status(g_shell);
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
