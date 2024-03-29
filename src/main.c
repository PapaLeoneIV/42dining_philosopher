/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:17 by rileone           #+#    #+#             */
/*   Updated: 2024/03/29 19:03:38 by rileone          ###   ########.fr       */
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

void *routine(void *room)
{
    t_room staz = *(t_room*)room;
    pthread_mutex_lock(&staz.stampa);
    write(2, "abcdef12345abcdef12345abcdef12345abcdef12345abcdef12345abcdef12345abcdef12345abcdef12345\n", 89);
    pthread_mutex_unlock(&staz.stampa);
    (void )staz;
    return NULL;
}

static int check_valid_args(int argc, char **argv)
{
    int i;    

    i = 1;
    if (argc < 5 || argc > 6)
        return (0);
    while (i < argc)
    {
        if(argv[i] && (!ft_isnumber(argv[i]) || ft_atoi(argv[i]) <= 0))
			return (0);
		i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_room tab;
    pthread_t thread_id;
    int     n_philo;

    tab = (t_room){0};
    n_philo = 0;
    if (ft_init_room(&tab, argc, argv) != 1 || check_valid_args(argc, argv) != 1)
        return (0);
    while(n_philo < tab.n_philos)
    {
        pthread_create(&thread_id, NULL, routine, (void * )&tab);
        n_philo++;
    }
    return (0);
}





