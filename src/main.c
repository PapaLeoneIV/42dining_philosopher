/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/03/18 11:53:48 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * 
 * argomenti: 
 * number_of_philosophers 
 * time_to_die
 * time_to_eat 
 * time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
*/

#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_philo var;

    var = (t_philo){0};
    if (argc < 5 || argc > 6)
        return (0);
    ft_init_var(&var, argv);
    return (0);
}