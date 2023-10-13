/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/13 15:53:07 by bverdeci         ###   ########.fr       */
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

//static char *replace_env_var(char *str)
//{
//	int		i;
//	char	*tmp;
//
//	i = 0;
//	while (str[i])
//	{
//		printf("%c\n", str[i]);
//		if (str[i] == '$' && str[i + 1] == '?')
//		{
//			//TODO replace str with the status
//			printf("%d\n",g_status);
//		}
//		i ++;
//	}
//}

void	add_cmd_args(t_parser **cmd, t_token **tokens)
{
	t_parser	*tmp;
	t_token		*tok;
	int			i;

	tmp = *cmd;
	tok = *tokens;
	tmp->cmd = ft_strdup(tok->str);
	if (ft_strcmp(tmp->cmd, "\0") == 0)
		tmp->cmd = " ";
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

void	init_cmd(t_parser **cmd)
{
	t_parser	*tmp;

	*cmd = malloc(sizeof(t_parser));
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

t_parser	*create_cmd(t_token **tokens)
{
	t_parser	*cmd;
	t_token		*start;

	start = *tokens;
	init_cmd(&cmd);
	while (*tokens && (*tokens)->type != E_PIPE && (*tokens)->type != E_HEREDOC)
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
		if (*tokens && (*tokens)->type != E_PIPE
			&& (*tokens)->type != E_HEREDOC)
			*tokens = (*tokens)->next;
	}
	return (cmd);
}
