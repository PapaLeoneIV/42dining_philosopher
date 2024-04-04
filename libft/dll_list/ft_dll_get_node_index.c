/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_get_node_index.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft.h"

int	ft_dll_get_node_index(t_dll_list *list, int value)
{
	int			i;
	t_dll_list	*ptr;

	i = 0;
	ptr = list;
	if (!list)
		return (-1);
	ft_dll_return_head(&ptr);
	while (ptr != NULL)
	{
		if (*(int *)ptr->val == value)
			return (i);
		ptr = ptr->next;
		i++;
	}
	return (-1);
}
