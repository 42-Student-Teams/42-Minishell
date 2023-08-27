/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:11:50 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/27 21:24:20 by bverdeci         ###   ########.fr       */
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
