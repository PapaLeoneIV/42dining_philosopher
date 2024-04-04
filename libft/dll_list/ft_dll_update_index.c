/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_update_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft.h"

void	ft_dll_update_index(t_dll_list **head)
{
	int	index;

	index = 0;
	ft_dll_return_head(head);
	while ((*head) != NULL)
	{
		(*head)->index = index;
		if ((*head)->next == NULL)
			break ;
		(*head) = (*head)->next;
		index++;
	}
	ft_dll_return_head(head);
}
