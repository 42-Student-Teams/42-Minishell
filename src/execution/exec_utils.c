/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:00:25 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/28 19:23:47 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *env)
{
	char	**paths;
	t_env	*tmp;

	paths = NULL;
	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	paths = ft_split(tmp->value, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	return (paths);
}

int	parser_len(t_parser *lst)
{
	t_parser	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static int	env_len(t_env *lst)
{
	t_env	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**from_chaintotab(t_env *env)
{
	t_env	*tmp;
	char	**new;
	char	*word_eq;
	int		len;
	int		i;

	tmp = env;
	len = env_len(env);
	new = ft_calloc(sizeof(char *), len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (tmp)
	{
		word_eq = ft_strjoin(tmp->key, "=");
		new[i] = ft_strjoin(word_eq, tmp->value);
		tmp = tmp->next;
		free(word_eq);
		i++;
	}
	return (new);
}

int	**create_pipes(int nb_cmds)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * nb_cmds);
	if (!pipes)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < nb_cmds)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < nb_cmds)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_putendl_fd("pipe error", STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
	}
	return (pipes);
}
