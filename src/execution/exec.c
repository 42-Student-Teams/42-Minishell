/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:10 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/27 18:15:37 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_parser **cmds, t_global *g_shell)
{
	t_parser	*tmp;
	int			nb_cmds;
	int			**pipes;

	tmp = *cmds;
	pipes = NULL;
	nb_cmds = parser_len(tmp);
	while (tmp && (ft_strcmp("<<", tmp->cmd) == 0))
	{
		heredoc(tmp->args[0]);
		tmp = tmp->next;
	}
	if (tmp && nb_cmds == 1 && is_builtin(tmp->cmd))
	{
		builtins(tmp, g_shell);
		return ;
	}
	if (!tmp)
		return ;
	pipes = create_pipes(nb_cmds);
	ft_process(*cmds, tmp, pipes, g_shell);
	waiting_pid(*cmds, &g_shell->status);
	free_pipes(pipes, nb_cmds);
}
