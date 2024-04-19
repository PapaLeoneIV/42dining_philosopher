/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:06:08 by rileone           #+#    #+#             */
/*   Updated: 2024/04/19 15:16:04 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_valid_args(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (argv[i] && (!ft_isnumber(argv[i]) || ft_atoi(argv[i]) <= 0))
			return (0);
		i++;
	}
	return (1);
}

void	ft_send_message(t_philo *ph, int flag)
{
	int		continuee;
	long	time;

	pthread_mutex_lock(&ph->stanza->continuee_mutex);
	continuee = ph->stanza->continuee;
	pthread_mutex_unlock(&ph->stanza->continuee_mutex);
	pthread_mutex_lock(&ph->stanza->stampa);
	if (continuee)
	{
		time = ft_get_time_msec() - ph->stanza->start_time;
		if (flag == FORKS)
			printf("%ld %i \033[32mhas taken a fork\033[0m\n", time, ph->id);
		else if (flag == DIED)
			printf("\033 [%ld %i died\033[0m\n", time, ph->id);
		else if (flag == SLEEP)
			printf("%ld %i \033[34mis sleeping\033[0m\n", time, ph->id);
		else if (flag == THINK)
			printf("%ld %i is thinking\033[0m\n", time, ph->id);
		else if (flag == EAT)
			printf("%ld %i \033[35mis eating\n\033[0m\n", time, ph->id);
	}
	pthread_mutex_unlock(&ph->stanza->stampa);
}

void	ft_take_forks(t_philo *philo)
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

void	ft_is_eating(t_philo *philo)
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

int	check_status(t_philo *philo)
{
	int	status;
	int	i;

	pthread_mutex_lock(&philo->stanza->continuee_mutex);
	i = philo->stanza->continuee;
	pthread_mutex_unlock(&philo->stanza->continuee_mutex);
	status = 1;
	if (i == 0)
		status = 0;
	return (status);
}
