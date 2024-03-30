/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:11 by rileone           #+#    #+#             */
/*   Updated: 2024/03/30 18:05:43 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <pthread.h>
# include <sys/time.h>



typedef struct s_waiter
{
    int numero_di_cicli;
    long start_time; 
    long end_time;
    int philos_alive;  //keeps track of the state of the philos;
} t_waiter;

typedef struct s_philo
{
    int id;
    int is_alive;   //each thread needs to know if its philo is alive
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_must_eat;
    
    long start_eat;
    long end_eat;
    long start_sleep;
    long end_sleep;


    pthread_mutex_t stampa;
    pthread_mutex_t lfork;
    pthread_mutex_t rfork;

} t_philo;


typedef struct s_stanza //contiene le regole del gioco e tutte le info del tavolo
{
    int n_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_must_eat;
    useconds_t delay;
    t_philo *philos;
    t_waiter waiter;       //he is going to be the observer of the dinner;
    

    pthread_t pthread_id;
    pthread_t wthread_id;
    pthread_mutex_t stampa;
    pthread_mutex_t mangia;
    pthread_mutex_t morte;
    pthread_mutex_t* forks;
    
} t_room;


int ft_init_room(t_room *var, int argc,  char **argv);
int check_valid_args(char **argv, int argc);


#endif