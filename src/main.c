/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/14 12:37:02 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

static void ft_send_message(t_philo *philo, int flag)
{
	int continuee;
	pthread_mutex_lock(&philo->stanza->continuee_mutex);
	continuee = philo->stanza->continuee;
	pthread_mutex_unlock(&philo->stanza->continuee_mutex);
	pthread_mutex_lock(&philo->stanza->stampa);
	if (continuee)
	{
		long timestamp = ft_get_time_msec() - philo->stanza->start_time;
		if (flag == FORKS)
			printf("%ld %i \033[32mhas taken a fork\033[0m\n",timestamp, philo->id);
		else if (flag == DIED)
			printf("\033 [%ld %i died\033[0m\n",  timestamp, philo->id);
		else if (flag == SLEEP)
			printf("%ld %i \033[34mis sleeping\033[0m\n",  timestamp, philo->id);
		else if (flag == THINK)
			printf("%ld %i is thinking\033[0m\n",  timestamp, philo->id);
		else if (flag == EAT)
			printf("%ld %i \033[35mis eating\n\033[0m\n",  timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->stanza->stampa);
}

void ft_take_forks(t_philo *philo)
{
	if (philo->id == philo->stanza->n_philos)
	{
		pthread_mutex_lock(philo->lfork);
		ft_send_message(philo, FORKS);
		pthread_mutex_lock(philo->rfork);
		ft_send_message(philo, FORKS);	
	}
	else
{
		pthread_mutex_lock(philo->rfork);
		ft_send_message(philo, FORKS);
		pthread_mutex_lock(philo->lfork);
		ft_send_message(philo, FORKS);
	}
}

void ft_is_eating(t_philo *philo)
{
	
	ft_take_forks(philo);
	ft_send_message(philo, EAT); 
	custom_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_lock(&philo->mend_eat);
	philo->end_eat = ft_get_time_msec();
	pthread_mutex_unlock(&philo->mend_eat);
}


int check_status(t_philo *philo)
{
    int status;
	int i;

	pthread_mutex_lock(&philo->stanza->continuee_mutex);
	i = philo->stanza->continuee;
	pthread_mutex_unlock(&philo->stanza->continuee_mutex);
    status = 1;
	if (i == 0)
        status = 0;
    return (status);
}


void *philoroutine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int must_eat;
	if (philo->id % 2)
		usleep(1000);
	if (philo->id % philo->stanza->n_philos && philo->id != 0) 
		usleep(2000);
	pthread_mutex_lock(&philo->mmust_eat);
	must_eat = philo->time_must_eat;
	pthread_mutex_unlock(&philo->mmust_eat);
	while(check_status(philo) && must_eat != 0)
	{
		ft_is_eating(philo);
		ft_send_message(philo, SLEEP);
		custom_sleep(philo->time_to_sleep);
		ft_send_message(philo, THINK);
		must_eat--;
	}
	pthread_exit(NULL);
}

void *bigbro(void *room)
{
	t_room *stanza = (t_room *)room;
	int i;

	while (1)
	{
		i = 0;
		while (i < stanza->n_philos)
		{
			pthread_mutex_lock(&stanza->philos[i].mend_eat);
			long int diff = ft_get_time_msec() - stanza->philos[i].end_eat;
			pthread_mutex_unlock(&stanza->philos[i].mend_eat);
			if (diff  > stanza->time_to_die)
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

void *lonelyboyroutine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	ft_send_message(philo, FORKS);
	custom_sleep(philo->time_to_sleep);
	ft_send_message(philo, DIED);

	pthread_exit(NULL);
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
	if (tab->n_philos == 1)
		pthread_create(&tab->pthread_id[0], NULL, &lonelyboyroutine, &(*(tab->philos)));
	else
	{
		while (++i < tab->n_philos)
		{
			pthread_create(&tab->pthread_id[i], NULL, &philoroutine, &(*(tab->philos + i)));		
			if(i == tab->n_philos - 1)
				pthread_create(&tab->wthread_id, NULL, &bigbro, tab);				
		}	
	}
	i = -1;
	while(++i < tab->n_philos)
		pthread_join(tab->pthread_id[i], NULL);
	return (0);
}
