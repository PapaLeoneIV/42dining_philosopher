/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:06:08 by rileone           #+#    #+#             */
/*   Updated: 2024/03/30 17:07:21 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int check_valid_args(char **argv, int argc)
{
    int i;    

    i = 1;
    if (argc < 5 || argc > 6)
        return (0);
    while (i < argc)
    {
        if(argv[i] && (!ft_isnumber(argv[i]) || ft_atoi(argv[i]) <= 0))
			return (0);
		i++;
    }
    return (1);
}