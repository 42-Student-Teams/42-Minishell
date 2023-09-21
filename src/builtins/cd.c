/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:37 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/09/21 14:14:49 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char *path)
{
	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

char	*get_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	return (ft_strdup(tmp->value));
}

static void	change_pwd(t_env **env_l, char *old_pwd)
{
	t_env	*tmp;
	char	*pwd;

	tmp = *env_l;
	pwd = malloc(1024);
	getcwd(pwd, 1024);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
		}
		else if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
}

int	my_cd(char **args, t_env **env_l)
{
	char	*path;
	char	*old_pwd;

	path = NULL;
	old_pwd = get_oldpwd(*env_l);
	if (args[1])
		path = args[1];
	if (exec_cd(path) == 1)
	{
		g_status = 1;
		return (1);
	}
	change_pwd(env_l, old_pwd);
	free(old_pwd);
	g_status = 0;
	return (0);
}
