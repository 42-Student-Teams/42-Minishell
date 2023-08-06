/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:49 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/06 11:43:13 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void my_pwd(void)
{
	char *buff;
	
	buff = malloc(1024);
	if (!buff)
	{
		ft_putendl_fd("malloc error", 2);
		return ;
	}
	getcwd(buff, 1024);
	printf("%s\n", buff);
	free(buff);
}
