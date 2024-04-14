/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 13:17:06 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philor(void *arg)
{
	t_philo	*philo;
	int		must_eat;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	if (philo->id % philo->stanza->n_philos && philo->id != 0)
		usleep(2000);
	pthread_mutex_lock(&philo->mmust_eat);
	must_eat = philo->time_must_eat;
	pthread_mutex_unlock(&philo->mmust_eat);
	while (check_status(philo) && must_eat != 0)
	{
		ft_is_eating(philo);
		ft_send_message(philo, SLEEP);
		custom_sleep(philo->time_to_sleep);
		ft_send_message(philo, THINK);
		must_eat--;
	}
	pthread_exit(NULL);
}

void	*bigbro(void *room)
{
	t_room		*stanza;
	long int	diff;
	int			i;

	stanza = (t_room *)room;
	while (1)
	{
		i = 0;
		while (i < stanza->n_philos)
		{
			pthread_mutex_lock(&stanza->philos[i].mend_eat);
			diff = ft_get_time_msec() - stanza->philos[i].end_eat;
			pthread_mutex_unlock(&stanza->philos[i].mend_eat);
			if (diff > stanza->time_to_die)
			{
				ft_send_message(&stanza->philos[i], DIED);
				pthread_mutex_lock(&stanza->continuee_mutex);
				stanza->continuee = 0;
				pthread_mutex_unlock(&stanza->continuee_mutex);
				pthread_exit(NULL);
			}
			i++;
		}
	}
}

void	*solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_send_message(philo, FORKS);
	custom_sleep(philo->time_to_sleep);
	ft_send_message(philo, DIED);
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_room	*tab;
	int		i;

	tab = ft_calloc(1, sizeof(t_room));
	i = -1;
	if (check_valid_args(argv, argc) != 1 || ft_init_room(tab, argc, argv) != 1)
		exit(EXIT_FAILURE);
	if (tab->n_philos == 1)
		pthread_create(&tab->t_id[0], NULL, &solo, &(*(tab->philos)));
	else
	{
		while (++i < tab->n_philos)
		{
			pthread_create(&tab->t_id[i], NULL, &philor, &(*(tab->philos + i)));
			if (i == tab->n_philos - 1)
				pthread_create(&tab->wthread_id, NULL, &bigbro, tab);
		}
	}
	i = -1;
	while (++i < tab->n_philos)
		pthread_join(tab->t_id[i], NULL);
	return (0);
}
