/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/13 15:44:43 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_exec(t_global *g_shell, t_parser **tmp, int nb_cmds)
{
	while (*tmp && (*tmp)->cmd && (ft_strcmp("<<", (*tmp)->cmd) == 0))
	{
		if ((*tmp)->args[0])
			heredoc((*tmp)->args[0]);
		else
		{
			ft_putendl_fd("bash: syntax error near unexpected token `newline'",
				STDERR_FILENO);
			g_status = 2;
			return (1);
		}
		*tmp = (*tmp)->next;
	}
	if (*tmp && (*tmp)->cmd && nb_cmds == 1 && is_spe_builtin((*tmp)->cmd))
	{
		if (is_spe_builtin((*tmp)->cmd) == 1)
			builtins(*tmp, g_shell);
		return (1);
	}
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
	free_pipes(pipes, nb_cmds);
}

