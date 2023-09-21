/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:49 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/09/21 14:16:25 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(void)
{
	char	*buff;

	buff = malloc(1024);
	if (!buff)
	{
		ft_putendl_fd("malloc error", STDERR_FILENO);
		g_status = 1;
		return (1);
	}
	getcwd(buff, 1024);
	ft_putendl_fd(buff, STDOUT_FILENO);
	free(buff);
	g_status = 0;
	return (0);
}
