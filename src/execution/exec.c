/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:10 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/21 17:26:03 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_exec(t_global *g_shell, t_parser **tmp, int nb_cmds)
{
	while (*tmp && (ft_strcmp("<<", (*tmp)->cmd) == 0))
	{
		if ((*tmp)->args[0])
			heredoc((*tmp)->args[0]);
		else
		{
			ft_putendl_fd("bash: syntax error near unexpected token `newline'",
				STDERR_FILENO);
			g_status = 258;
			return (1);
		}
		*tmp = (*tmp)->next;
	}
	if (*tmp && nb_cmds == 1 && is_spe_builtin((*tmp)->cmd))
		builtins(*tmp, g_shell);
	return (0);
}

void	execution(t_parser **cmds, t_global *g_shell)
{
	t_parser	*tmp;
	int			nb_cmds;
	int			**pipes;

	tmp = *cmds;
	pipes = NULL;
	nb_cmds = parser_len(tmp);
	g_shell->nb_cmds = nb_cmds;
	if (pre_exec(g_shell, &tmp, nb_cmds) == 1)
		return ;
	if (!tmp)
		return ;
	pipes = create_pipes(nb_cmds);
	ft_process(*cmds, tmp, pipes, g_shell);
	waiting_pid(*cmds, &g_shell->status);
	free_pipes(pipes, nb_cmds);
}

