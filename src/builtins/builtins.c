/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:26:01 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/14 18:46:34 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	commands(char **args, char *cmd, t_global *g_shell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		g_shell->status = my_cd(args, &g_shell->env_l);
	else if (ft_strcmp(cmd, "echo") == 0)
		g_shell->status = my_echo(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		g_shell->status = my_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		g_shell->status = my_env(args, g_shell);
	else if (ft_strcmp(cmd, "export") == 0)
		g_shell->status = my_export(args, &g_shell->env_l);
	else if (ft_strcmp(cmd, "unset") == 0)
		g_shell->status = my_unset(&g_shell->env_l, args, -1);
	else if (ft_strcmp(cmd, "exit") == 0)
		g_shell->status = my_exit(args);
}

int	is_variable(char *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] == '=' && cmd[i + 1])
			return (1);
	}
	return (0);
}

void	builtins(t_parser *cmd, t_global *g_shell)
{
	t_parser	*tmp;
	char		**args;
	char		*key;

	tmp = cmd;
	if (is_variable(tmp->cmd))
	{
		while (tmp && is_variable(tmp->cmd))
		{
			args = ft_calloc(sizeof(char *), 3);
			if (!args)
				return ;
			args[0] = ft_strdup("export");
			args[1] = ft_strdup(tmp->cmd);
			key = ft_substr(args[1], 0, ft_strchr(args[1], '=') - args[1]);
			if (key_in_env(key, g_shell->env_l))
				g_shell->status = my_export(args, &g_shell->env_l);
			else
				g_shell->status = my_vars(args, &g_shell->vars);
			free_strtab(args);
			tmp = tmp->next;
		}
		return ;
	}
	commands(cmd->args, cmd->cmd, g_shell);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (is_variable(cmd))
		return (1);
	str_tolower(cmd);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	is_spe_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (is_variable(cmd))
		return (1);
	else if (ft_strcmp(cmd, "Cd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "CD") == 0)
		return (2);
	else if (ft_strcmp(cmd, "cD") == 0)
		return (2);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}
