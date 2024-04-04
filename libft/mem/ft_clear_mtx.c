/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_clear_mtx(char ***mtx, int len)
{
	int	i;

	i = 0;
	if (!mtx || !(*mtx) || !(**mtx))
		return ;
	while (i < len)
	{
		free(*(*mtx + i));
		*(*mtx + i) = NULL;
		i++;
	}
	free(*(mtx));
	*(mtx) = NULL;
}
