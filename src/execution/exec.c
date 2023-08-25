/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:10 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/25 19:40:03 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_env *env)
{
	char	**paths;
	t_env	*tmp;

	paths = NULL;
	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	paths = ft_split(tmp->value, ':');
	if (!paths)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (paths);
}

int	lst_len(t_parser *lst)
{
	t_parser	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	(*create_pipes(int nb_cmds))[2]
{
	int	(*pipes)[2];
	int	i;

	pipes = malloc(sizeof(int *) * nb_cmds);
	if (!pipes)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < nb_cmds)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_putendl_fd("pipe error", STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
	}
	return (pipes);
}

void	process_exec(t_parser *cmd, t_global *g_shell)
{
	(void)cmd;
	(void)g_shell;
}

void	execution(t_parser **cmds, t_global *g_shell)
{
	t_parser	*tmp;
	int			nb_cmds;
	int			(*pipes)[2];
	char		**paths;
	int			i;

	tmp = *cmds;
	nb_cmds = lst_len((void *) tmp);
	pipes = create_pipes(nb_cmds);
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp->pid = fork();
		if (tmp->pid < 0)
		{
			ft_putendl_fd("fork error", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (tmp->pid == 0)
		{
			printf("PROCESS %d\n", i);
			if (tmp->infile != 0)
				dup2(tmp->infile, STDIN_FILENO);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (tmp->outfile != 1)
				dup2(tmp->outfile, STDOUT_FILENO);
			else if (tmp->next)
				dup2(pipes[i][1], STDOUT_FILENO);
			close(pipes[i][0]);
			close(pipes[i][1]);
			process_exec(tmp, g_shell);
			exit (EXIT_SUCCESS);
		}
		tmp = tmp->next;
		i++;
	}
	tmp = *cmds;
	while (tmp)
	{
		waitpid(tmp->pid, &(g_shell)->status, 0);
		tmp = tmp->next;
	}
	paths = get_paths(g_shell->env_l);
}
