/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:26 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/10/14 17:34:33 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:49:23 by bverdeci          #+#    #+#             */
/*   Updated: 2023/09/28 22:43:16 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_value(char *var, t_env	*vars)
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

void	add_variable(char *new, char *var, t_env *env, int *i)
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
			return ;
		}
		tmp = tmp->next;
	}
}

char	*change_str(char *str, t_global *g_shell)
{
	int		len;

	if (check_quotes(str))
	{
		len = new_len(str, g_shell->env_l, g_shell->vars);
		return (new_str(str, len, g_shell->env_l, g_shell->vars));
	}
	ft_putstr_fd("bash: unexpected EOF while looking for matching \"\'",
		STDERR_FILENO);
	return (NULL);
}

int	check_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			if (!check_next_quote(str, '"', &i))
			{
				return (0);
			}
		}
		if (str[i] == '\'')
		{
			if (!check_next_quote(str, '\'', &i))
				return (0);
		}
	}
	return (1);
}

int	check_next_quote(char *str, char c, int *i)
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
