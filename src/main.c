/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/03/30 20:14:05 by rileone          ###   ########.fr       */
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

void *philoroutine(void *philo)
{
    void *retval;
    t_philo *filos = (t_philo*)philo;
    
    if (filos == NULL)
        pthread_exit(&retval);
    while(1)
    {
        /**cercavo di usare gdb per capire perche non stampava
         * penso che saltasse da trhead a thread quando premevo next
         * 
        */
        ft_putnbr((int)ft_get_time_msec());
        custom_sleep(500);
    }
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

    
    
    
    
    
    return NULL;
}

/* void *waiter_routine(t_room room)
{
    
    return NULL;
} */



int main(int argc, char **argv)
{
    t_room tab;
    int     n_philo;

    tab = (t_room){0};
    n_philo = 0;
    if (check_valid_args(argv, argc) != 1 || ft_init_room(&tab, argc, argv) != 1 )
        return (0);
    while(n_philo < tab.n_philos)
    {
        pthread_create(&tab.pthread_id, NULL, philoroutine, (void * )&tab.philos[n_philo]);
        n_philo++;
    }
 /*    pthread_create(&tab.wthread_id, NULL, NULL, NULL); */
    return (0);
}





