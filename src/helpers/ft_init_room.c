/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:27:28 by rileone           #+#    #+#             */
/*   Updated: 2024/03/29 19:06:30 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void ft_assign_forks(t_room *room, t_philo *philo, int counter)
{
    philo->
}


//Each philosopher has a number ranging from 1 to number_of_philosophers
static int prepare_philos(t_room *room, char **argv)
{
    int i;

    i = -1;
    room->philos = ft_calloc(room->n_philos, sizeof(t_philo));
    if (!room->philos)
        return (0);
    while(++i < room->n_philos)
    {
        room->philos[i] = (t_philo){0};
        room->philos[i].id = i + 1;
        room->philos[i].is_alive = 1;
        room->philos[i].time_to_die = room->time_to_die;
        room->philos[i].time_to_eat = room->time_to_eat;
        room->philos[i].time_to_sleep = room->time_to_sleep;
        room->philos[i].time_must_eat = room->time_must_eat;
        ft_assign_forks(room, room->philos[i], i);
    }
    return (1);
}

static int address_dining_room(t_room *room, int argc, char **argv)
{
    int i;

    i = -1;
    while(++i < room->n_philos)
         pthread_mutex_init(room->forks + i, NULL);
    pthread_mutex_init(&room->stampa, NULL);
    pthread_mutex_init(&room->morte, NULL);
    pthread_mutex_init(&room->mangia, NULL);
    room->n_philos = ft_atoi(argv[1]);
    room->time_to_die = ft_atoi(argv[2]);
    room->time_to_eat = ft_atoi(argv[3]);
    room->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        room->time_must_eat = ft_atoi(argv[5]);
    return (1);
}
static int hire_waiter(t_room *room)
{
    room->waiter = (t_waiter){0};
    room->waiter.philos_alive = 1; 
    room->waiter.start_time = ft_get_time_msec();
    if (!room->waiter.start_time)
        return (0);
    return (1);
}

int ft_init_room(t_room *room, int argc, char **argv)
{
    /**devo sviluppare una funzione per liberare tutto in caso di errore*/
    if (check_valid_args(argv, argc) == 0)
        error_fn(INITIALIZATION_ERROR);
    if (address_dining_room(room, argc, argv) == 0)
        error_fn(INITIALIZATION_ERROR);
    if (hire_waiter(room) == 0)
        error_fn(INITIALIZATION_ERROR);
    if (prepare_philos(room, argv) == 0)
        error_fn(INITIALIZATION_ERROR);
    return (1);
}