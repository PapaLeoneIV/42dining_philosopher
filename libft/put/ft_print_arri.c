/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include "libft.h"

void	ft_print_arri(int *arr, int len)
{
	int	i;

	i = 0;
	ft_printf("\n[Arr] :");
	while (arr && i < len)
	{
		ft_printf("\tidx->[%i]  :  %i\n", i, arr[i]);
		i++;
	}
}
