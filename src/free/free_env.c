/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:47:29 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/06/30 20:50:30 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void free_env(t_env *env)
{
	t_env	*curr_env;
	
	*curr_env = *env;
	if (env->key || env->value)
	{
		while ()	
	}
}