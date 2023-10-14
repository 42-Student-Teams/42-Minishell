/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 19:21:42 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_parser **cmd)
{
	t_parser	*tmp;

	*cmd = malloc(sizeof(t_parser));
	if (!cmd)
		*cmd = NULL;
	tmp = *cmd;
	tmp->infile = 0;
	tmp->outfile = 1;
	tmp->nb_args = 0;
	tmp->index = 0;
	tmp->args = NULL;
	tmp->cmd = NULL;
	tmp->fullpath = NULL;
	tmp->next = NULL;
}

static void	open_infile(t_parser *cmd, t_token **tokens)
{
	cmd->infile = open((*tokens)->next->str, O_RDONLY);
	*tokens = (*tokens)->next->next;
}

t_parser	*create_cmd(t_token **tokens)
{
	t_parser	*cmd;
	t_token		*start;

	start = *tokens;
	init_cmd(&cmd);
	while (*tokens && (*tokens)->type != E_PIPE && (*tokens)->type != E_HEREDOC)
	{
		if (*tokens && (*tokens)->type == E_INFILE
			&& start == *tokens && (*tokens)->next)
			open_infile(cmd, tokens);
		if (*tokens && (*tokens)->str)
			add_cmd_args(&cmd, tokens);
		if (*tokens && (*tokens)->type == E_OUTFILE && (*tokens)->next)
		{
			cmd->outfile = open((*tokens)->next->str, O_CREAT
					| O_RDWR | O_TRUNC, 0666);
			*tokens = (*tokens)->next->next;
		}
		if (*tokens && (*tokens)->type != E_PIPE
			&& (*tokens)->type != E_HEREDOC)
			*tokens = (*tokens)->next;
	}
	return (cmd);
}
