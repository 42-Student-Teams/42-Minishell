/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:39:12 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/29 15:29:13 by lsaba-qu         ###   ########.fr       */
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
