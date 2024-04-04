/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/04/04 14:07:12 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *
 * argomenti:
 * number_of_philosophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
 */

#include "../includes/philo.h"

/* void ft_print_stats(t_room *tab, char **argv)
{
    int i;

    i = -1;
    ft_printf("Room Stats: \n");
    ft_printf("tab->n_philos : %i\n",tab->n_philos);
    ft_printf("tab->time_to_die : %i\n",tab->time_to_die);
    ft_printf("tab->time_to_eat : %i\n",tab->time_to_eat);
    ft_printf("tab->time_to_sleep : %i\n",tab->time_to_sleep);
    ft_printf("tab->time_must_eat : %i\n",tab->time_must_eat);
    ft_printf("---------\n");
    while(++i < ft_atoi(argv[1]))
    {
        ft_printf("STATISTIC OF PHILO N [%i]\n", i);
        ft_printf("tab->philosID : %i\n",tab->philos[i].id);
        ft_printf("tab->philos->isalive %i\n", tab->philos[i].is_alive);
        ft_printf("tab->philos->time_to_die : %i\n",tab->philos[i].time_to_die);
        ft_printf("tab->philos->time_to_eat : %i\n",tab->philos[i].time_to_eat);
        ft_printf("tab->philos->time_to_sleep : %i\n",tab->philos[i].time_to_sleep);
        ft_printf("tab->philos->time_must_eat : %i\n",tab->philos[i].time_must_eat);
    }
    ft_printf("WAITER STATS\n");
    ft_printf("numero di cicli %i\n", tab->waiter.numero_di_cicli);
    ft_printf("start->time %i\n", tab->waiter.start_time);
    ft_printf("they are alive %i\n", tab->waiter.philos_alive);

} */

void ft_send_message(t_philo *philo, int flag)
{
    pthread_mutex_lock(&philo->stampa);
    if (philo->is_alive)
    {
        if(flag == FORKS)
            printf("%ld %i has taken a fork\n",ft_get_time_msec() - philo->stanza->start_time, philo->id);
        if(flag == DIED)
            printf("%ld %i has died\n",  ft_get_time_msec() - philo->stanza->start_time, philo->id);
        if(flag == SLEEP)
            printf("%ld %i is sleeping\n",  ft_get_time_msec() - philo->stanza->start_time, philo->id);
        if(flag == THINK)
            printf("%ld %i has taken a fork\n",  ft_get_time_msec() - philo->stanza->start_time, philo->id);
        if(flag == EAT)
            printf("%ld %i is eating\n",  ft_get_time_msec() - philo->stanza->start_time, philo->id);
    }
    pthread_mutex_unlock(&philo->stampa);
}

void ft_take_forks(t_philo *philo)
{
    if (philo->id == philo->n_philos_tot)
    {
        pthread_mutex_lock(philo->rfork);
        ft_send_message(philo, FORKS);
        pthread_mutex_lock(philo->lfork);
        ft_send_message(philo, FORKS);
    }
    else
    {
        pthread_mutex_lock(philo->lfork);
        ft_send_message(philo, FORKS);
        pthread_mutex_lock(philo->rfork) ;
        ft_send_message(philo, FORKS);
    }
}

void ft_is_eating(t_philo *philo)
{
    //prende le forkette
    ft_take_forks(philo);
    
    //timestamp inizio pranzo 
    philo->start_eat = ft_get_time_msec();
    
    //scrive i messaggi
    ft_send_message(philo, EAT);
    
    //passa il tempo prestabilito
    
    
    //sblocco le forchette
    pthread_mutex_unlock(philo->rfork);
    pthread_mutex_unlock(philo->lfork);
    custom_sleep(philo->time_to_eat * 1000);
    //timestamp fine pranzo 
    philo->end_eat = ft_get_time_msec();
}

void ft_is_sleeping(t_philo *philo)
{
    ft_send_message(philo, SLEEP);
    custom_sleep(philo->time_to_sleep);
}

void ft_is_thinking(t_philo *philo)
{
    ft_send_message(philo, THINK);
}

void *philoroutine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while(philo->is_alive && philo->time_must_eat != 0)
    {
        ft_is_eating(philo);
        ft_is_sleeping(philo);
        ft_is_thinking(philo);       
        philo->time_must_eat--;
    }


    return (NULL);
}

/* void *waiter_routine(t_room room)
{

    return NULL;
} */
    /**
     * CONTROLLI DA FARE :
     *
     * controllare che il philo sia diverso da NULL
     *
     * //in un loop infinito devono :
     *
     * -mangiare
     *      (check sulle forks)
     *      (sleep_di(time_to_eat)time)
     *      (stampa X sta mangiando)
     * -pensare
     *      (sleep_di(time_to_think)time)
     *      (stampa X sta pensando)
     * -dormire
     *      (sleep_di(time_to_sleep)time)
     *      (stampa X sta dormendo)
     *
     */
int main(int argc, char **argv)
{
    t_room *tab;
    int i;
    
    tab = ft_calloc(1, sizeof(t_room));
    i = -1;
    if (check_valid_args(argv, argc) != 1 || ft_init_room(tab, argc, argv) != 1)
        return (0);
    while (++i < tab->n_philos)
    {
        tab->philos[i].creation_time = tab->start_time - ft_get_time_msec();
        pthread_create(&tab->pthread_id[i], NULL, &philoroutine, &(*(tab->philos + i)));
    }
    i = -1;
    while(++i < tab->n_philos)
        pthread_join(tab->pthread_id[i], NULL);
    return (0);
}
