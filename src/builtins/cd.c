/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:37 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/13 13:49:59 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(char	*path)
{
	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
