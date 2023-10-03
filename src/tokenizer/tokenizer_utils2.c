/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42l>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:36:58 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/03 17:12:56 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_len(char *str, t_env *env_l, t_env *vars)
{
	int		i;
	int		start;
	int		end;
	int		len;
	char	*variable;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					while (str[i] == '$')
					{
						start = i + 1;
						while (str[++i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '$')
							continue ;
						end = i;
						variable = ft_substr(str, start, end - start);
						variable = ft_strtrim(variable, "\"");
						if (key_in_env(variable, env_l))
							len += len_value(variable, env_l);
						else if (key_in_env(variable, vars))
							len += len_value(variable, vars);
						i = end;
					}
					if (variable)
						free(variable);
				}
				else
					len++;
				if (!str[i])
					return (len);
			}
		}
		else if (str[i] == '$')
		{
			while (str[i] == '$')
			{
				start = i + 1;
				while (str[++i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '$')
					continue ;
				end = i;
				variable = ft_substr(str, start, end - start);
				if (key_in_env(variable, env_l))
					len += len_value(variable, env_l);
				else if (key_in_env(variable, vars))
					len += len_value(variable, vars);
				i = end;
			}
		}
		else if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				len++;
		}
		else
			len++;
		if (!str[i])
			return (len);
	}
	return (len);
}

void	new_str(char *str, char *new, t_env *env_l, t_env *vars)
{
	int		i;
	int		start;
	int		end;
	int		j;
	char	*variable;

	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' && str[i])
		{
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					while (str[i] == '$')
					{
						start = i + 1;
						while (str[++i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '$')
							continue ;
						end = i;
						variable = ft_substr(str, start, end - start);
						variable = ft_strtrim(variable, "\"");
						if (key_in_env(variable, env_l))
							add_variable(new, variable, env_l, &j);
						else if (key_in_env(variable, vars))
							add_variable(new, variable, vars, &j);
						i = end;
					}
					if (variable)
						free(variable);
				}
				else
					new[j++] = str[i];
				if (!str[i])
					return ;
			}
		}
		else if (str[i] == '$' && str[i])
		{
			while (str[i] == '$')
			{
				start = i + 1;
				while (str[++i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '$')
					continue ;
				end = i;
				variable = ft_substr(str, start, end - start);
				if (key_in_env(variable, env_l))
					add_variable(new, variable, env_l, &j);
				else if (key_in_env(variable, vars))
					add_variable(new, variable, vars, &j);
				i = end;
			}
		}
		else if (str[i] == '\'' && str[i])
		{
			while (str[++i] && str[i] != '\'')
				new[j++] = str[i];
		}
		else
			new[j++] = str[i];
		if (!str[i])
			return ;
	}
}
