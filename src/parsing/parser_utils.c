/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:51:54 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/27 20:11:22 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_matching_quotes(char *str, char quote)
{
	char	*start;
	char	*end;
	size_t	len;
	char	*trimmed;

	start = str;
	end = str + strlen(str) - 1;
	while (*start == quote && *end == quote)
	{
		start++;
		end--;
	}
	len = end - start + 1;
	trimmed = malloc(len + 1);
	ft_strncpy(trimmed, start, len);
	trimmed[len] = '\0';
	return (trimmed);
}

void	trim_first_quote(char *command)
{
	char	*start;
	char	*end;

	start = command;
	while (*start && *start != '\'' && *start != '\"')
	{
		start++;
	}
	if (*start == '\'' || *start == '\"')
	{
		end = start;
		while (*end && *end != *start)
		{
			end++;
		}
		if (*end == *start)
		{
			while (*end)
			{
				*end = *(end + 1);
				end++;
			}
		}
	}
}

void	lst_add_cmd(t_parser **cmds, t_parser *cmd)
{
	t_parser	*tmp;

	if (*cmds == NULL)
	{
		*cmds = cmd;
		return ;
	}
	tmp = *cmds;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cmd;
}
