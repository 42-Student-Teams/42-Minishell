/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:19:38 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/06 08:15:01 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:19:38 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/06 08:14:46 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:39:12 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/30 18:08:08 by bverdeci         ###   ########.fr       */
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
