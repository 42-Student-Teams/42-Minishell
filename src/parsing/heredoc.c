/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:11:50 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/27 21:00:07 by lsaba-qu         ###   ########.fr       */
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
	}
	free(line);
	return (fd);
}

t_parser	*create_heredoc(t_token *tokens)
{
	t_parser	*cmd;

	cmd = malloc(sizeof(t_parser));
	init_cmd(&cmd);
	add_heredoc_args(&cmd, tokens);
	return (cmd);
}
