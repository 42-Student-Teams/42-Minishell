/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:11:50 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/28 17:57:09 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (fd);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (fd);
		}
		ft_putendl_fd(line, fd);
	}
	free(line);
	return (fd);
}

/*
** il faudra unlink le fichier .heredoc
*/

t_parser	*create_heredoc(t_token *tokens, t_global *g_shell)
{
	t_parser	*cmd;

	cmd = malloc(sizeof(t_parser));
	init_cmd(&cmd);
	g_shell->status = add_heredoc_args(&cmd, tokens);
	return (cmd);
}

int	add_heredoc_args(t_parser **cmd, t_token *tokens)
{
	t_parser	*tmp;
	t_token		*tok;

	tmp = *cmd;
	tok = tokens;
	tmp->cmd = ft_strdup("<<");
	tmp->args = ft_calloc(sizeof(char *), 2);
	if (!tmp->args)
		return (1);
	if (tok->next)
		tmp->args[0] = ft_strdup(tok->next->str);
	else
		return (258);
	return (0);
}