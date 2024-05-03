/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:55:29 by rileone           #+#    #+#             */
/*   Updated: 2024/05/03 13:25:06 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long	mutex_long_int_get(long *elem, pthread_mutex_t *mutex_addr)
{
	long	elem_out;

	pthread_mutex_lock(mutex_addr);
	elem_out = *elem;
	pthread_mutex_unlock(mutex_addr);
	return (elem_out);
}

int	mutex_int_get(int *elem, pthread_mutex_t *mutex_addr)
{
	int	elem_out;

	pthread_mutex_lock(mutex_addr);
	elem_out = *elem;
	pthread_mutex_unlock(mutex_addr);
	return (elem_out);
}

void	mutex_int_set(int *elem, pthread_mutex_t *mutex_addr, int value)
{
	pthread_mutex_lock(mutex_addr);
	*elem = value;
	pthread_mutex_unlock(mutex_addr);
}

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

void	clean_table(t_room *tab)
{
	int	i;

	i = -1;
	while (++i < tab->n_philos)
	{
		pthread_mutex_destroy(&tab->p[i].mend_eat);
		pthread_mutex_destroy(&tab->p[i].mmust_eat);
		pthread_mutex_destroy(tab->forks + i);
	}
	pthread_mutex_destroy(&tab->cmutex);
	pthread_mutex_destroy(&tab->stampa);
	free(tab->p);
	free(tab->forks);
	free(tab->t_id);
	free(tab);
}
