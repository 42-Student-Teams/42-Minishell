/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:49:43 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 16:28:47 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char **env)
{
	int		i;
	t_env	*env;

	i = 0;
	while (env[i])
		i ++;
	env = (t_env *)malloc(sizeof(t_env) * i + 1);
	if (!env)
		return (0);
	i = 0;
	// make a linked list with the env variables
	return (0);
}
