/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:11:50 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/25 20:07:15 by lsaba-qu         ###   ########.fr       */
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
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) - 1) == 0)
		{
			free(line);
			return (fd);
		}
	}
	free(line);
	return (fd);
}

/*
** il faudra unlink le fichier .heredoc
*/
