/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/05/03 13:24:46 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	if (philo->id % philo->stanza->n_philos && philo->id != 0)
		usleep(2000);
	while (check_status(philo) && check_must_eat(philo))
	{
		ft_is_eating(philo);
		ft_send_message(philo, SLEEP);
		custom_sleep(philo->time_to_sleep);
		ft_send_message(philo, THINK);
		pthread_mutex_lock(&philo->mmust_eat);
		philo->must_eat--;
		pthread_mutex_unlock(&philo->mmust_eat);
	}
	pthread_exit(NULL);
}

void	*waiterr(void *room)
{
	t_room		*stz;
	long int	diff;
	long int	tmp;
	int			must_eat;
	int			i;

	stz = (t_room *)room;
	while (1)
	{
		i = -1;
		while (++i < stz->n_philos)
		{
			must_eat = mutex_int_get(&stz->p[i].must_eat, &stz->p[i].mmust_eat);
			tmp = mutex_long_int_get(&stz->p[i].end_eat, &stz->p[i].mend_eat);
			diff = ft_get_time_msec() - tmp;
			if (diff > stz->time_to_die)
			{
				if (must_eat == 0)
					return (mutex_int_set(&stz->cont, &stz->cmutex, 0), NULL);
				ft_send_message(&stz->p[i], DIED);
				mutex_int_set(&stz->cont, &stz->cmutex, 0);
				pthread_exit(NULL);
			}
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
		return (free(tab), 1);
	if (tab->n_philos == UN_SOLO_PHILO)
		pthread_create(&tab->t_id[0], NULL, &solo, &(*(tab->p)));
	else
	{
		while (++i < tab->n_philos)
		{
			pthread_create(&tab->t_id[i], NULL, &philor, &(*(tab->p + i)));
			if ((i == tab->n_philos - 1) && tab->n_philos > UN_SOLO_PHILO)
				pthread_create(&tab->wthread_id, NULL, &waiterr, tab);
		}
	}
	if (tab->n_philos > UN_SOLO_PHILO)
		pthread_join(tab->wthread_id, NULL);
	i = -1;
	while (++i < tab->n_philos)
		pthread_join(tab->t_id[i], NULL);
	clean_table(tab);
	return (0);
}
