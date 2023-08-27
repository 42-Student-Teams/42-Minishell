/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:20:25 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/27 20:08:48 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strtab(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_pipes(int **pipes, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(pipes[i]);
	free(pipes);
}

void	free_process(char **paths, char **env, char *command)
{
	free_strtab(paths);
	free_strtab(env);
	free(command);
	ft_putendl_fd("Minishell: command not found", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
