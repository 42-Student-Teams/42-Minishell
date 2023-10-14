/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:58:42 by bverdeci          #+#    #+#             */
/*   Updated: 2023/10/14 17:54:05 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_doubleq_next(int *i, t_env *vars, char *str, t_env *env_l)
{
	t_utils	utils;

	utils = (t_utils){};
	utils.new = ft_calloc(sizeof(char), 100000);
	if (!utils.new)
		return (NULL);
	utils.j = 0;
	while (str[*i] == '$')
	{
		utils.start = *i + 1;
		while (str[++(*i)] && !ft_isspace(str[*i])
			&& str[*i] != '\'' && str[*i] != '$')
			continue ;
		utils.end = *i;
		utils.variable = ft_substr(str, utils.start, utils.end - utils.start);
		utils.variable = ft_strtrim(utils.variable, "\"");
		if (key_in_env(utils.variable, env_l))
			add_variable(utils.new, utils.variable, env_l, &utils.j);
		else if (key_in_env(utils.variable, vars))
			add_variable(utils.new, utils.variable, vars, &utils.j);
		*i = utils.end;
	}
	if (utils.variable)
		free(utils.variable);
	return (utils.new);
}


char	*process_doubleq(int *i, t_env *vars, char *str, t_env *env_l)
{
	char	*new;
	char	*tmp;
	int		j;

	new = ft_calloc(sizeof(char), 100000);
	if (!new)
		return (NULL);
	j = 0;
	while (str[++(*i)] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			tmp = process_doubleq_next(i, vars, str, env_l);
			new = ft_strcat(new, tmp);
		}
		else
			new[j++] = str[*i];
		if (!str[*i])
			return (new);
	}
	return (new);
}

char	*process_singleq(int *i, t_env *vars, char *str, t_env *env_l)
{
	char	*new;
	int		start;
	int		end;
	int		j;
	char	*variable;

	new = ft_calloc(sizeof(char), 100000);
	if (!new)
		return (NULL);
	j = 0;
	while (str[*i] == '$')
	{
		start = *i + 1;
		while (str[++(*i)] && !ft_isspace(str[*i])
			&& str[*i] != '\'' && str[*i] != '$')
			continue ;
		end = *i;
		variable = ft_substr(str, start, end - start);
		if (key_in_env(variable, env_l))
			add_variable(new, variable, env_l, &j);
		else if (key_in_env(variable, vars))
			add_variable(new, variable, vars, &j);
		*i = end;
	}
	return (new);
}

void	big_process_str(t_utils *utils, t_env *vars, t_env *env_l, char *str)
{
	if (str[utils->i] == '"' && str[utils->i])
	{
		utils->variable = process_doubleq(&utils->i, vars, str, env_l);
		utils->new = ft_strcat(utils->new, utils->variable);
		free(utils->variable);
	}
	else if (str[utils->i] == '$' && str[utils->i])
	{
		utils->variable = process_singleq(&utils->i, vars, str, env_l);
		utils->new = ft_strcat(utils->new, utils->variable);
		free(utils->variable);
	}
	else if (str[utils->i] == '\'' && str[utils->i])
	{
		while (str[++utils->i] && str[utils->i] != '\'')
			utils->new[utils->j++] = str[utils->i];
	}
	else
		utils->new[utils->j++] = str[utils->i];
}

char	*new_str(char *str, int len, t_env *env_l, t_env *vars)
{
	t_utils	utils;

	utils.new = ft_calloc(sizeof(char), len + 1);
	if (!utils.new)
		return (NULL);
	utils.j = 0;
	utils.i = -1;
	while (str[++utils.i])
	{
		big_process_str(&utils, vars, env_l, str);
		if (!str[utils.i])
			return (utils.new);
	}
	return (utils.new);
}
