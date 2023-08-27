/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:38:18 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/26 14:05:33 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(char *src, char c)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	if (src)
		len = ft_strlen((const char *)src);
	else
		len = 0;
	ret = malloc(sizeof(char) * len + 2);
	if (!ret)
		return (NULL);
	if (src)
	{
		while (src[i])
		{	
			ret[i] = src[i];
			i++;
		}
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}
