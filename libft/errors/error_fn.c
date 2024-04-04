/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:17 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	error_fn(t_errors error_type)
{
	if (error_type == INITIALIZATION_ERROR)
		perror("Error in the initialization phase");
	else if (error_type == ALLOCATION_ERROR)
		perror("Error in allocation!!!");
	else if (error_type == EXEC_ERROR)
		perror("Error the execution of function!!");
	else if (error_type == INVALID_INPUT)
		perror("Error nell input passato!!");
	exit(EXIT_FAILURE);
}
