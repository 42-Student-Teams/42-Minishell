/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:49 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/19 19:42:32 by lsaba-qu         ###   ########.fr       */
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
		return (1);
	}
	getcwd(buff, 1024);
	ft_putendl_fd(buff, STDOUT_FILENO);
	free(buff);
	return (0);
}