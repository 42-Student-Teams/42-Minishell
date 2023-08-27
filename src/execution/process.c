/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:19:06 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/27 21:55:39 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exec(t_parser *cmd, t_global *g_shell)
{
	char	**paths;
	char	*path_cmd;
	char	**env;
	char	*command;
	int		i;

	if (is_builtin(cmd->cmd))
	{
		builtins(cmd, g_shell);
		exit(g_shell->status);
	}
	paths = get_paths(g_shell->env_l);
	env = from_chaintotab(g_shell->env_l);
	if (ft_strncmp("/", cmd->cmd, 1) == 0)
	{
		if (access(cmd->cmd, F_OK) == 0)
		{
			if (execve(cmd->cmd, cmd->args, env) == -1)
				throw_error(NULL);
		}
	}
	command = ft_strjoin("/", cmd->cmd);
	i = -1;
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], command);
		if (access(path_cmd, F_OK) == 0)
		{
			if (execve(path_cmd, cmd->args, env) == -1)
				throw_error(NULL);
		}
		free(path_cmd);
	}
	free_strtab(paths);
	free_strtab(env);
	free(command);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

void	prepare_exec(t_parser *tmp, int **pipes, int *i)
{
	int	j;

	if (tmp->infile != 0)
		dup2(tmp->infile, STDIN_FILENO);
	else if (*i > 0)
		dup2(pipes[*i - 1][0], STDIN_FILENO);
	if (tmp->outfile != 1)
		dup2(tmp->outfile, STDOUT_FILENO);
	else if (tmp->next)
		dup2(pipes[*i][1], STDOUT_FILENO);
	j = -1;
	while (++j < tmp->nb_args - 1)
	{
		if (j != *i - 1)
			close(pipes[j][0]);
		if (j != *i)
			close(pipes[j][1]);
	}
}

void	waiting_pid(t_parser *cmds, int *status)
{
	t_parser	*tmp;

	tmp = cmds;
	while (tmp)
	{
		waitpid(tmp->pid, status, 0);
		tmp = tmp->next;
	}
}

void	ft_process(t_parser *cmds, t_parser *tmp,
					int **pipes, t_global *g_shell)
{
	int	i;

	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp->pid = fork();
		if (tmp->pid < 0)
			throw_error("fork error");
		if (tmp->pid == 0)
		{
			prepare_exec(tmp, pipes, &i);
			process_exec(tmp, g_shell);
			exit (EXIT_SUCCESS);
		}
		close(pipes[i][1]);
		tmp = tmp->next;
		i++;
	}
	waiting_pid(cmds, &i);
	if (WIFEXITED(i))
		g_shell->status = WEXITSTATUS(i);
}
