/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:18:01 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/03/03 15:23:48 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *str)
{
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == 0)
		return (1);
	return (0);
}
