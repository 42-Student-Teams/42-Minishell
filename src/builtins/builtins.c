/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:26:01 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/27 11:52:19 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	commands(char **args, char *cmd, t_global *g_shell)
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
}

void	builtins(t_parser *cmd, t_global *g_shell)
{
	commands(cmd->args, cmd->cmd, g_shell);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
