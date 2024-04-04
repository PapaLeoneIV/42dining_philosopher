/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_printi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft.h"
#include "ft_printf.h"

void	ft_dll_printi(t_dll_list *list)
{
	t_dll_list	*ptr;

	ptr = list;
	ft_printf("\n[Lista] : ");
	while (ptr != NULL)
	{
		ft_printf("\n\tidx->[%i]  :  [%i]", ptr->index, *(int *)(ptr->val));
		ptr = ptr->next;
	}
	ft_printf("\n");
}
