/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:39:12 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/28 15:03:55 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_parser **cmds, t_token *tokens, t_global *g_shell)
{
	t_token		*tok;

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
	tok = tokens;
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

