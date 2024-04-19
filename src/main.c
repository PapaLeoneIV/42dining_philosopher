/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/19 15:22:48 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_must_eat(t_philo *philo)
{
	int	must_eat_copy;

	pthread_mutex_lock(&philo->mmust_eat);
	must_eat_copy = philo->must_eat;
	pthread_mutex_unlock(&philo->mmust_eat);
	if (must_eat_copy == 0)
		return (0);
	return (1);
}

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
	t_room		*stanza;
	long int	diff;
	int			must_eat;
	int			i;

	stanza = (t_room *)room;
	while (1)
	{
		i = 0;
		while (i < stanza->n_philos)
		{
			pthread_mutex_lock(&stanza->philos[i].mmust_eat);
			must_eat = stanza->philos->must_eat;
			pthread_mutex_unlock(&stanza->philos[i].mmust_eat);
			pthread_mutex_lock(&stanza->philos[i].mend_eat);
			diff = ft_get_time_msec() - stanza->philos[i].end_eat;
			pthread_mutex_unlock(&stanza->philos[i].mend_eat);
			if (diff > stanza->time_to_die)
			{
				if (must_eat == 0)
				{
					pthread_mutex_lock(&stanza->continuee_mutex);
					stanza->continuee = 0;
					pthread_mutex_unlock(&stanza->continuee_mutex);
					return (NULL);
				}
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

void	clean_table(t_room *tab)
{
	int	i;

	i = -1;
	while (++i < tab->n_philos)
	{
		pthread_mutex_destroy(&tab->philos[i].mend_eat);
		pthread_mutex_destroy(&tab->philos[i].mmust_eat);
		pthread_mutex_destroy(tab->forks + i);
	}
	pthread_mutex_destroy(&tab->continuee_mutex);
	pthread_mutex_destroy(&tab->stampa);
	free(tab->philos);
	free(tab->forks);
	free(tab->t_id);
	free(tab);
}

int	main(int argc, char **argv)
{
	t_room	*tab;
	int		i;

	tab = ft_calloc(1, sizeof(t_room));
	i = -1;
	if (check_valid_args(argv, argc) != 1 || ft_init_room(tab, argc, argv) != 1)
		return (free(tab), 1);
	if (tab->n_philos == 1)
		pthread_create(&tab->t_id[0], NULL, &solo, &(*(tab->philos)));
	else
	{
		while (++i < tab->n_philos)
		{
			pthread_create(&tab->t_id[i], NULL, &philor, &(*(tab->philos + i)));
			if ((i == tab->n_philos - 1) && tab->n_philos > 1)
				pthread_create(&tab->wthread_id, NULL, &waiterr, tab);
		}
	}
	if(tab->n_philos > 1)
		pthread_join(tab->wthread_id, NULL);
	i = -1;
	while (++i < tab->n_philos)
		pthread_join(tab->t_id[i], NULL);
	clean_table(tab);
	return (0);
}
