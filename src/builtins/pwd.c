/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:49 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/16 11:49:53 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(void)
{
	char	*buff;

	buff = malloc(1024);
	if (!buff)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		return ;
	}
	getcwd(buff, 1024);
	ft_putendl_fd(buff, STDOUT_FILENO);
	free(buff);
}
