/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:28:07 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/17 20:28:17 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* gets t_list at index, supports negative indexes */
t_list	*ft_lst_get(t_list *lst, ssize_t index)
{
	ssize_t	i;

	if (!lst)
		return (NULL);
	if (index < 0)
		index = ft_lstsize(lst) + index;
	if (index < 0)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (i == index)
			return (lst);
		lst = lst->next;
		i ++;
	}
	return (NULL);
}