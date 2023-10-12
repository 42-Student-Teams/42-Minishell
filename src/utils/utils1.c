/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bverdeci <bverdeci@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:21:08 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/09/26 08:19:33 by bverdeci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	printinfo(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

static int	ft_isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

void	str_tolower(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isupper(s[i]))
			ft_tolower(s[i]);
	}
}