/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:36:58 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 16:59:30 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_doubleq_var(int	*i, t_env *vars, char *str, t_env *env_l)
{
	int		start;
	int		end;
	char	*variable;
	int		len;

	len = 0;
	while (str[*i] == '$')
	{
		start = *i + 1;
		while (str[++(*i)] && !ft_isspace(str[*i])
			&& str[*i] != '\'' && str[*i] != '$')
			continue ;
		end = *i;
		variable = ft_substr(str, start, end - start);
		variable = ft_strtrim(variable, "\"");
		if (key_in_env(variable, env_l))
			len += len_value(variable, env_l);
		else if (key_in_env(variable, vars))
			len += len_value(variable, vars);
		*i = end;
	}
	if (variable)
		free(variable);
	return (len);
}


static int	check_doubleq_var(int *i, t_env *vars, char *str, t_env *env_l)
{
	int		len;

	len = 0;
	while (str[++(*i)] && str[*i] != '"')
	{
		if (str[*i] == '$')
			len += process_doubleq_var(i, vars, str, env_l);
		else
			len++;
		if (!str[*i])
			return (len);
	}
	return (len);
}

static int	check_singleq_var(int	*i, t_env *vars, char *str, t_env *env_l)
{
	int		start;
	int		end;
	char	*variable;
	int		len;

	start = 0;
	end = 0;
	len = 0;
	while (str[*i] == '$')
	{
		start = *i + 1;
		while (str[++(*i)] && !ft_isspace(str[*i])
			&& str[*i] != '\'' && str[*i] != '$')
			continue ;
		end = *i;
		variable = ft_substr(str, start, end - start);
		if (key_in_env(variable, env_l))
			len += len_value(variable, env_l);
		else if (key_in_env(variable, vars))
			len += len_value(variable, vars);
		*i = end;
	}
	if (variable)
		free(variable);
	return (len);
}

static int	skip_squotes(int *i, char *str)
{
	int	len;

	len = 0;
	while (str[++(*i)] && str[*i] != '\'')
		len++;
	return (len);
}

int	new_len(char *str, t_env *env_l, t_env *vars)
{
	int		i;
	int		len;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			len += check_doubleq_var(&i, vars, str, env_l);
			if (!str[i])
				return (len);
		}
		else if (str[i] == '$')
			len += check_singleq_var(&i, vars, str, env_l);
		else if (str[i] == '\'')
			len += skip_squotes(&i, str);
		else
			len++;
		if (!str[i])
			return (len);
	}
	return (len);
}
