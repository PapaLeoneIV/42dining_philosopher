/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:27:28 by rileone           #+#    #+#             */
/*   Updated: 2024/05/03 12:56:25 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_assign_forks(t_room *room, t_philo *philo)
{
	if (philo->id == 1)
	{
		philo->rfork = &room->forks[room->n_philos - 1];
		philo->lfork = &room->forks[0];
	}
	else if (philo->id == room->n_philos)
	{
		philo->rfork = &room->forks[room->n_philos - 1];
		philo->lfork = &room->forks[room->n_philos - 2];
	}
	else
	{
		philo->lfork = &room->forks[philo->id - 1];
		philo->rfork = &room->forks[philo->id - 2];
	}
}

int	prepare_philos(t_room *room)
{
	int	i;

	i = -1;
	room->p = ft_calloc(room->n_philos, sizeof(t_philo));
	if (!room->p)
		return (0);
	while (++i < room->n_philos)
	{
		room->p[i] = (t_philo){0};
		room->p[i].id = i + 1;
		room->p[i].is_alive = 1;
		room->p[i].time_to_die = room->time_to_die;
		room->p[i].time_to_eat = room->time_to_eat;
		room->p[i].time_to_sleep = room->time_to_sleep;
		room->p[i].time_must_eat = room->time_must_eat;
		room->p[i].n_philos_tot = room->n_philos;
		room->p[i].stanza = room;
		room->p[i].must_eat = room->time_must_eat;
		room->p[i].end_eat = ft_get_time_msec();
		ft_assign_forks(room, &room->p[i]);
		pthread_mutex_init(&room->p[i].mend_eat, NULL);
		pthread_mutex_init(&room->p[i].mmust_eat, NULL);
	}
	return (1);
}

static int	address_dining_room(t_room *room, int argc, char **argv)
{
	int	i;

	i = -1;
	room->n_philos = ft_atoi(argv[1]);
	room->time_to_die = ft_atoi(argv[2]);
	room->time_to_eat = ft_atoi(argv[3]);
	room->time_to_sleep = ft_atoi(argv[4]);
	room->cont = 1;
	room->start_time = ft_get_time_msec();
	room->t_id = ft_calloc(room->n_philos, sizeof(pthread_t));
	if (argc == 6)
		room->time_must_eat = ft_atoi(argv[5]);
	else
		room->time_must_eat = -1;
	room->forks = ft_calloc(room->n_philos, sizeof(pthread_mutex_t));
	while (++i < room->n_philos)
		pthread_mutex_init(&(room->forks[i]), NULL);
	pthread_mutex_init(&room->stampa, NULL);
	pthread_mutex_init(&room->cmutex, NULL);
	return (1);
}

int	ft_init_room(t_room *room, int argc, char **argv)
{
	if (check_valid_args(argv, argc) == 0)
		error_fn(INITIALIZATION_ERROR);
	if (address_dining_room(room, argc, argv) == 0)
		error_fn(INITIALIZATION_ERROR);
	if (prepare_philos(room) == 0)
		error_fn(INITIALIZATION_ERROR);
	return (1);
}
