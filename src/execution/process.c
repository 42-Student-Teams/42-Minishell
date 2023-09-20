/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:19:06 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/20 12:32:29 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exec(t_parser *cmd, t_global *g_shell)
{
	exec_cmd(cmd, g_shell, -1);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_status = 127;
	exit(127);
}

void	prepare_exec(t_parser *tmp, int **pipes, int *i, int nb_cmds)
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
	while (++j < nb_cmds - 1)
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
			prepare_exec(tmp, pipes, &i, g_shell->nb_cmds);
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
