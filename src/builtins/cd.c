/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:37 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/07 11:08:19 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char	*path)
{
	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

int	my_cd(char **args)
{
	char	*path;

	path = NULL;
	if (args[1])
		path = args[1];
	if (exec_cd(path) == 1)
		return (1);
	return (0);
}
