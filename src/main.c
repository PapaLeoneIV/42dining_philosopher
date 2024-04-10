/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/10 12:26:51 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

static void ft_send_message(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->stanza->stampa);
	long timestamp = ft_get_time_msec() - philo->stanza->start_time;
	pthread_mutex_lock(&philo->alive);
	if (philo->is_alive)
	{
		if (flag == FORKS)
			printf("%ld %i \033[32mhas taken the fork\033[0m\n",timestamp, philo->id);
		else if (flag == DIED)
			printf("\033 [%ld %i has died\033[0m\n",  timestamp, philo->id);
		else if (flag == SLEEP)
			printf("%ld %i \033[34mis sleeping\033[0m\n",  timestamp, philo->id);
		else if (flag == THINK)
			printf("%ld %i is thinking\033[0m\n",  timestamp, philo->id);
		else if (flag == EAT)
			printf("%ld %i \033[35mis eating\n\033[0m\n",  timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->alive);
	pthread_mutex_unlock(&philo->stanza->stampa);
}

void ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	ft_send_message(philo, FORKS);
	pthread_mutex_lock(philo->lfork);
	ft_send_message(philo, FORKS);
}

void ft_is_eating(t_philo *philo)
{
	
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->start_eat = ft_get_time_msec();
	ft_send_message(philo, EAT);                           
	custom_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	philo->end_eat = ft_get_time_msec();
	pthread_mutex_unlock(&philo->lock);
}


int check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->is_alive == 0)
	{
		philo->stanza->continuee = 0;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

int check_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->stanza->continuee == 0)		
	{
		pthread_mutex_unlock(&philo->lock);
		return (0);	
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void *philoroutine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while(check_death(philo) && check_continue(philo) && philo->time_must_eat != 0)
	{
		ft_is_eating(philo);
		ft_send_message(philo, SLEEP);
		custom_sleep(philo->time_to_sleep);
		ft_send_message(philo, THINK);
		philo->time_must_eat--;
	}
		
	return (NULL);
}

int bigbro(t_room *room)
{
	int i;
	
	while (1)
	{
		i = -1;
		while (++i < room->n_philos)
		{
			pthread_mutex_lock(&room->philos[i].lock);
			if (ft_get_time_msec() - room->philos[i].end_eat > room->time_to_die)
			{
				ft_send_message(&room->philos[i], DIED);
				pthread_mutex_lock(&room->philos[i].alive);
				room->philos[i].is_alive = 0;
				pthread_mutex_unlock(&room->philos[i].alive);
				pthread_mutex_unlock(&room->philos[i].lock);
				return (1);
			}
			pthread_mutex_unlock(&room->philos[i].lock);
		}
		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	t_room *tab;
	int i;
	
	tab = ft_calloc(1, sizeof(t_room));
	i = -1;
	if (check_valid_args(argv, argc) != 1 || ft_init_room(tab, argc, argv) != 1) {
		return (1);
	}
	while (++i < tab->n_philos)
	{
		tab->philos[i].creation_time = tab->start_time - ft_get_time_msec();
		pthread_create(&tab->pthread_id[i], NULL, &philoroutine, &(*(tab->philos + i)));
	}
	i = -1;
	bigbro(tab);
	i = -1;
	while(++i < tab->n_philos)
		pthread_join(tab->pthread_id[i], NULL);
	return (0);
}
