/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/13 23:21:07 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exec(t_parser *cmd, t_global *g_shell)
{
	if (cmd->infile < 0)
	{
		ft_putendl_fd("bash: No such file or directory", STDERR_FILENO);
		exit(1);
	}
	if (!cmd->cmd)
		exit(0);
	exec_cmd(cmd, g_shell, -1);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_status = 127;
	assign_g_status(g_shell);
	exit(g_status);
}

void	prepare_exec(t_parser *tmp, int **pipes, int nb_cmds)
{
	int	j;
	int	i;

	i = tmp->index;
	j = -1;
	while (++j < nb_cmds - 1)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
	}
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (tmp->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	if (tmp->infile > 0)
		dup2(tmp->infile, STDIN_FILENO);
	if (tmp->outfile != 1)
		dup2(tmp->outfile, STDOUT_FILENO);
}

static int	ret_utils(int ret, int status)
{
	while (ret != -1)
	{
		ret = waitpid(-1, &status, 0);
	}
	return (ret);
}

int	waiting_pid(void)
{
	int	ret;
	int	status;

	status = 0;
	ret = 0;
	ret = ret_utils(ret, status);
	if (errno == ECHILD)
	{
		errno = 0;
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGBUS)
				printf("Bus error: 10\n");
			return (WTERMSIG(status) + 128);
		}
		else if (WIFSTOPPED(status))
			return (WSTOPSIG(status) + 128);
		else if (WIFCONTINUED(status))
			return (0);
		return (0);
	}
	return (0);
}

void	ft_process(t_parser *cmds, t_parser *tmp,
	int **pipes, t_global *g_shell)
{
	int	i;

	i = 0;
	(void)cmds;
	init_termios(2);
	while (tmp)
	{
		tmp->index = i;
		tmp->pid = fork();
		if (tmp->pid < 0)
			throw_error("fork error");
		if (tmp->pid == 0)
		{
			prepare_exec(tmp, pipes, g_shell->nb_cmds);
			process_exec(tmp, g_shell);
			exit (EXIT_SUCCESS);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(pipes, g_shell->nb_cmds);
	g_status = waiting_pid();
	init_termios(1);
}
