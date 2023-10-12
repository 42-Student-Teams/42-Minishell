/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:59:17 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/30 17:13:43 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(t_parser *cmd, t_global *g_shell)
{
	if (is_builtin(cmd->cmd))
	{
		builtins(cmd, g_shell);
		exit(g_status);
	}
}

static void	exec_abs_paths(t_parser *cmd, char **env)
{
	if (ft_strncmp("/", cmd->cmd, 1) == 0)
	{
		if (access(cmd->cmd, F_OK) == 0)
		{
			if (execve(cmd->cmd, cmd->args, env) == -1)
				throw_error(NULL);
		}
	}
	if (ft_strncmp("./", cmd->cmd, 2) == 0)
	{
		if (access(cmd->cmd, F_OK) == 0)
		{
			if (execve(cmd->cmd, cmd->args, env) == -1)
				throw_error(NULL);
		}
	}
}

void	exec_cmd(t_parser *cmd, t_global *g_shell, int i)
{
	char	**paths;
	char	*path_cmd;
	char	**env_tab;
	char	*command;

	paths = NULL;
	command = NULL;
	exec_builtin(cmd, g_shell);
	env_tab = from_chaintotab(g_shell->env_l);
	exec_abs_paths(cmd, env_tab);
	command = ft_strjoin("/", cmd->cmd);
	paths = get_paths(g_shell->env_l);
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], command);
		if (access(path_cmd, F_OK) == 0)
		{
			if (execve(path_cmd, cmd->args, env_tab) == -1)
				throw_error(NULL);
		}
		free(path_cmd);
	}
	free_strtab(paths);
	free_strtab(env_tab);
	free(command);
}
