/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:20:02 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/17 20:31:33 by lsaba-qu         ###   ########.fr       */
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

int	handle_string(t_token **token, char *s, int index)
{
	(void)token;
	(void)s;
	(void)index;
	return (0);
}

int	lexer(t_token **token, char *s, int index)
{
	char c1;
	char c2;

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


int	insert_token_into_lst(enum e_token_type t, char *value, t_token **lst, int i)
{
	t_token	*new;

	new = ft_lstnewtoken(t, value);
	ft_lstadd_back((t_list **)&lst, (t_list *)new);
	return (i);
}