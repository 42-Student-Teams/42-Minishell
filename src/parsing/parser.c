/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:39:12 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/25 15:40:56 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_args(t_parser **cmd, t_token **tokens)
{
	t_parser	*tmp;
	t_token		*tok;
	int			i;

	tmp = *cmd;
	tok = *tokens;
	tmp->cmd = ft_strdup(tok->str);
	tok = tok->next;
	while (tok && tok->str)
	{
		tok = tok->next;
		tmp->nb_args++;
	}
	tmp->args = ft_calloc(sizeof(char *), tmp->nb_args + 1);
	if (!tmp->args)
		return ;
	tok = (*tokens)->next;
	i = -1;
	while (tok && tok->str)
	{
		tmp->args[++i] = ft_strdup(tok->str);
		tok = tok->next;
	}
	*tokens = tok;
	i = -1;
}

void	init_cmd(t_parser **cmd)
{
	t_parser	*tmp;

	tmp = *cmd;
	tmp->infile = 0;
	tmp->outfile = 1;
	tmp->nb_args = 0;
	tmp->args = NULL;
	tmp->cmd = NULL;
	tmp->fullpath = NULL;
	tmp->next = NULL;
}

t_parser	*create_cmd(t_token **tokens)
{
	t_parser	*cmd;
	t_token		*start;

	cmd = malloc(sizeof(t_parser));
	start = *tokens;
	init_cmd(&cmd);
	while (*tokens && (*tokens)->type != E_PIPE)
	{
		if (*tokens && (*tokens)->type == E_INFILE && start == *tokens)
		{
			cmd->infile = open((*tokens)->next->str, O_RDONLY);
			*tokens = (*tokens)->next->next;
		}
		if (*tokens && (*tokens)->str)
			add_cmd_args(&cmd, tokens);
		if (*tokens && (*tokens)->type == E_OUTFILE)
		{
			cmd->outfile = open((*tokens)->next->str, O_CREAT
					| O_RDWR | O_TRUNC, 0666);
			*tokens = (*tokens)->next->next;
		}
		if (*tokens && (*tokens)->type != E_PIPE)
			*tokens = (*tokens)->next;
	}
	return (cmd);
}

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

void	parser(t_parser **cmds, t_token *tokens)
{
	t_token		*tok;

	tok = tokens;
	while (tok)
	{
		lst_add_cmd(cmds, create_cmd(&tok));
		if (tok)
			tok = tok->next;
	}
}
