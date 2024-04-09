/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/08 17:21:16 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

static void ft_send_message(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->stanza->stampa);
	long timestamp = ft_get_time_msec() - philo->stanza->start_time;
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

void *philoroutine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while(philo->is_alive && philo->time_must_eat != 0)
	{
		ft_is_eating(philo);
		ft_send_message(philo, SLEEP);
		custom_sleep(philo->time_to_sleep);
		ft_send_message(philo, THINK);
		philo->time_must_eat--;
	}
	return (NULL);
}

int check_death(t_room *stanza)
{
	int i;

	i = 0;
	
	while(i < stanza->n_philos)
	{
		
		if(stanza->philos[i].end_eat - stanza->philos[i].start_eat > stanza->philos[i].time_to_die)
		{
			/**stampa la morte del filosofo*/
			ft_send_message(&stanza->philos[i], DIED);
			/**interrmpi esecuzione*/
			return (0);
		}
		i++;
	}
	return (1);
}
/* 
void bigbrother(t_room * room)
{
	pthread_mutex_lock(&room->stampa);
	if (check_death(room) == 0)
	{
		pthread_mutex_unlock(&room->stampa);	
		return;
	}
	pthread_mutex_unlock(&room->stampa);
} */

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
/* 	bigbro();
 */	i = -1;
	while(++i < tab->n_philos)
		pthread_join(tab->pthread_id[i], NULL);
	return (0);
}
