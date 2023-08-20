/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:20:02 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:40 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_istoken(char *s, int index)
{
	char	c1;
	char	c2;

	c1 = s[index];
	c2 = s[index + 1];
	if (c1 == '|')
		return (1);
	else if (c1 == '>' && c2 == '>')
		return (1);
	else if (c1 == '<' && c2 == '<')
		return (1);
	else if (c1 == '>' && c2 != '>')
		return (1);
	else if (c1 == '<' && c2 != '<')
		return (1);
	return (0);
}

int	handle_string(t_token **token, char *s, int index)
{
	int		end;
	char	*str;

	end = index;
	while (s[++end])
	{
		if (ft_isspace(s[end]))
			break ;
		if (ft_istoken(s, end))
			break ;
	}
	str = ft_substr(s, index, end - index);
	end = ft_strlen(str);
	insert_token_into_lst(E_WORD, str, token, 0);
	return (end);
}

int	lexer(t_token **token, char *s, int index)
{
	char	c1;
	char	c2;

	c1 = s[index];
	c2 = s[index + 1];
	if (c1 == '|')
		return (insert_token_into_lst(E_PIPE, NULL, token, 1));
	else if (c1 == '>' && c2 == '>')
		return (insert_token_into_lst(E_APPEND, NULL, token, 2));
	else if (c1 == '<' && c2 == '<')
		return (insert_token_into_lst(E_HEREDOC, NULL, token, 2));
	else if (c1 == '>' && c2 != '>')
		return (insert_token_into_lst(E_OUTFILE, NULL, token, 1));
	else if (c1 == '<' && c2 != '<')
		return (insert_token_into_lst(E_INFILE, NULL, token, 1));
	else if (ft_isspace(c1))
	{
		return (1);
	}
	else
		return (handle_string(token, s, index));
}

int	insert_token_into_lst(enum e_token_type t, char *value,
		t_token **lst, int i)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_lstnewtoken(t, value);
	tmp = *lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		return (i);
	}
	*lst = new;
	return (i);
}
