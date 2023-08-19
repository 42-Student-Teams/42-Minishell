/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:26:01 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/19 16:19:20 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	commands(char **args, char *cmd, t_global *g_shell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		g_shell->status = my_cd(args, &g_shell->env_l);
	else if (ft_strcmp(cmd, "echo") == 0)
		g_shell->status = my_echo(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		g_shell->status = my_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		g_shell->status = my_env(args, g_shell);
	else if (ft_strcmp(cmd, "export") == 0)
		g_shell->status = my_export(args, &g_shell->env_l);
	else if (ft_strcmp(cmd, "unset") == 0)
		g_shell->status = my_unset(&g_shell->env_l, args, -1);
	else if (ft_strcmp(cmd, "exit") == 0)
		g_shell->status = my_exit(args);
	return (0);
}

int	builtins(char *input, t_global *g_shell)
{
	char	**args;
	char	*cmd;

	if (input[0] == ' ')
		return (0);
	args = ft_split(input, ' ');
	if (args == NULL)
		return (0);
	cmd = args[0];
	if (commands(args, cmd, g_shell) == 1)
		return (1);
	free_split(args);
	return (0);
}
