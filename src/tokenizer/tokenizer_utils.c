/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:49:23 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/27 17:17:39 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnewtoken(enum e_token_type type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

static int	check_next_quote(char *str, char c, int *i)
{
	while (str[++(*i)])
	{
		if (str[*i] == c)
		{
			return (1);
		}
	}
	return (0);
}

static int	check_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			if (!check_next_quote(str, '"', &i))
				return (0);
		}
		if (str[i] == '\'')
		{
			if (!check_next_quote(str, '\'', &i))
				return (0);
		}
	}
	return (1);
}

static int	len_value(char *var, t_env	*vars)
{
	t_env	*tmp;

	tmp = vars;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->key) == 0)
			return (ft_strlen(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

static int	new_len(char *str, t_env *env_l, t_env *vars)
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
					start = i + 1;
					while (str[++i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '$')
						continue ;
					end = i;
					variable = ft_substr(str, start, end - start);
					if (key_in_env(variable, env_l))
						len += len_value(variable, env_l);
					else if (key_in_env(variable, vars))
						len += len_value(variable, vars);
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
		else if (ft_isalnum(str[i]))
			len++;
		if (!str[i])
			return (len);
	}
	return (len);
}

static void	add_variable(char *new, char *var, t_env *env, int *i)
{
	t_env	*tmp;
	int		j;

	tmp = env;
	j = -1;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			while (tmp->value[++j])
			{
				new[*i] = tmp->value[j];
				(*i)++;
			}
			printf("PRINT : %s\n ", new);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	new_str(char *str, char *new, t_env *env_l, t_env *vars)
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
					// ft_putendl_fd(variable, 1);
					if (key_in_env(variable, env_l))
						add_variable(new, variable, env_l, &j);
					else if (key_in_env(variable, vars))
						add_variable(new, variable, vars, &j);
					i = end;
					}
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
		{
			new[j++] = str[i];
		}
		if (!str[i])
			return ;
	}
}

char	*change_str(char *str, t_global *g_shell)
{
	int		len;
	char	*new;

	new = NULL;
	if (check_quotes(str))
	{
		len = new_len(str, g_shell->env_l, g_shell->vars);
		printf("len = %d\n", len);
		new = ft_calloc(sizeof(char), len + 1);
		new_str(str, new, g_shell->env_l, g_shell->vars);
		return (new);
	}
	ft_putendl_fd("bash: unexpected EOF while looking for matching \"\'",
		STDERR_FILENO);
	return (NULL);
}
