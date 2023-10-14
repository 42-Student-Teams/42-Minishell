/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:11:38 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/14 19:12:15 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_cmd(t_parser **cmds, t_parser *cmd)
{
	t_parser	*tmp;

	if (*cmds == NULL)
	{
		*cmds = cmd;
		return ;
	}
	tmp = *cmds;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cmd;
}

static void	init_cmd_args(t_parser *tmp, char *str)
{
	tmp->cmd = ft_strdup(str);
	if (ft_strcmp(tmp->cmd, "\0") == 0)
		tmp->cmd = " ";
}

void	add_cmd_args(t_parser **cmd, t_token **tokens)
{
	t_parser	*tmp;
	t_token		*tok;
	int			i;

	tmp = *cmd;
	tok = *tokens;
	init_cmd_args(tmp, tok->str);
	while (tok && tok->str)
	{
		tok = tok->next;
		tmp->nb_args++;
	}
	if (tok && tok->type == E_HEREDOC)
		tmp->infile = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	tmp->args = ft_calloc(sizeof(char *), tmp->nb_args + 1);
	if (!tmp->args)
		return ;
	tok = *tokens;
	i = -1;
	while (tok && tok->str)
	{
		tmp->args[++i] = ft_strdup(tok->str);
		tok = tok->next;
	}
	*tokens = tok;
}
