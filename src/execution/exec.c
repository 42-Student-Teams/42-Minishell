/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:10 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/25 15:39:25 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prototype from copilot (bad)

void	exec_cmd(t_parser *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->fullpath, cmd->args, env->envp) == -1)
			printinfo("minishell: %s: %s\n", cmd->cmd, strerror(errno));
		exit(0);
	}
	else if (pid < 0)
		printinfo("minishell: %s\n", strerror(errno));
	else
		waitpid(pid, &status, 0);
}
