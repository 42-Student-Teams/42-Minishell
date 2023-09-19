/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:06:10 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/09/19 16:48:26 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i ++;
	}
	return (i);
}

// #include <stdio.h>
// int main ()
// {
// 	int e = 0;
// 	char tab[] = "sadsd";

// 	e = ft_strlen(tab);

// 	printf("%d", e);
// }