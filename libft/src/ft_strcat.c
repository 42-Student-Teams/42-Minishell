/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:03:52 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/04/28 15:06:28 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (dest[len])
	{
		len ++;
	}
	while (src[i])
	{
		if (src[i])
			dest[len + i] = src[i];
		i ++;
	}
	dest[i + len] = '\0';
	return (dest);
}
