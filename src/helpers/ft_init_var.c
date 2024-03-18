/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:27:28 by rileone           #+#    #+#             */
/*   Updated: 2024/03/18 11:53:45 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int ft_init_var(t_philo *var, char **argv)
{
    if(argv[1])
        var->n_philo = ft_atoi(argv[1]);
    if (argv[2])
        var->time_to_die = ft_atoi(argv[2]);
    if (argv[3])
        var->time_to_eat = ft_atoi(argv[3]);
    if (argv[4])
        var->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        var->time_to_die = ft_atoi(argv[5]);
    return 1;
}