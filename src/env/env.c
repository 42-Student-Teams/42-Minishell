/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:49:43 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/07/20 16:43:39 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//test
int	init_env(t_shell *shell, char **env)
{
	while (*env && env)
	{
		shell->env = (t_env *)malloc(sizeof(t_env));
		if (shell->env == NULL)
			return (-1);
		shell->env->key = ft_substr(*env, 0, ft_strchr(*env, '=') - *env);
		shell->env->value = ft_substr(*env, ft_strchr(*env, '=') - *env + 1, ft_strlen(*env));
		//prints the key and value of the env when using export
		// printf("declare -x %s=%s\n", shell->env->key, shell->env->value);
		env++; 
	}
	return (0);
}


// Doesn't work it aborts at line 42 !!!!!
// void	print_env(t_env *env)
// {
// 	t_env *current;

// 	current = env;
// 	while (current)
// 	{
// 		printf("declare -x %s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// }