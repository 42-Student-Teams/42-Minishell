/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:19:38 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 19:05:42 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_heredoc(t_token *tokens, t_parser **cmds, t_global *g_shell)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (tok && tok->type == E_HEREDOC)
		{
			lst_add_cmd(cmds, create_heredoc(tok, g_shell));
			if (tok->next)
				tok = tok->next->next;
			else
				tok = tok->next;
		}
		else
			tok = tok->next;
	}
}

void	parser(t_parser **cmds, t_token *tokens, t_global *g_shell)
{
	t_token		*tok;

	tok = tokens;
	parse_heredoc(tok, cmds, g_shell);
	while (tok)
	{
		if (tok->type == E_HEREDOC)
		{
			if (tok->next)
				tok = tok->next->next;
			else
				tok = tok->next;
		}
		else
		{
			lst_add_cmd(cmds, create_cmd(&tok));
			if (tok && tok->type != E_HEREDOC)
				tok = tok->next;
		}
	}
}
