/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 18:40:48 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_interrupt(int signal)
{
	if (signal == SIGINT)
		g_status = 1;
}

int	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	init_termios(3);
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (!g_status)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(line))))
		{
			free(line);
			return (fd);
		}
		ft_putendl_fd(line, fd);
	}
	free(line);
	close(fd);
	g_status = 0;
	init_termios(1);
	return (g_status);
}
/*
** il faudra unlink le fichier .heredoc
*/

t_parser	*create_heredoc(t_token *tokens, t_global *g_shell)
{
	t_parser	*cmd;

	(void)g_shell;
	cmd = malloc(sizeof(t_parser));
	if (!cmd)
		return (NULL);
	init_cmd(&cmd);
	g_status = add_heredoc_args(&cmd, tokens);
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
	if (tok->next && tok->next->str)
		tmp->args[0] = ft_strdup(tok->next->str);
	else
		return (127);
	return (0);
}
