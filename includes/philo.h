/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:11 by rileone           #+#    #+#             */
/*   Updated: 2024/05/03 13:24:34 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_stanza	t_stanza;

# define UN_SOLO_PHILO 1

typedef enum e_actions
{
	FORKS,
	PRINT,
	DIED,
	THINK,
	SLEEP,
	EAT,
}	t_actions;

typedef struct s_philo
{
	int					id;
	int					n_philos_tot;
	int					is_alive;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_must_eat;
	int					must_eat;
	long int			start_eat;
	long int			end_eat;
	pthread_mutex_t		mmust_eat;
	pthread_mutex_t		mend_eat;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	t_stanza			*stanza;
}	t_philo;

typedef struct s_stanza
{
	t_philo				*p;
	int					n_philos;
	int					counter;
	int					time_to_sleep;
	int					time_to_die;
	int					time_to_eat;
	int					time_must_eat;
	int					cont;
	long int			start_time;
	pthread_t			*t_id;
	pthread_t			wthread_id;
	pthread_mutex_t		*forks;
	pthread_mutex_t		cmutex;
	pthread_mutex_t		stampa;
}	t_room;

int			ft_init_room(t_room *var, int argc, char **argv);
int			check_valid_args(char **argv, int argc);
void		ft_send_message(t_philo *philo, int flag);
void		ft_take_forks(t_philo *philo);
void		ft_is_eating(t_philo *philo);
int			check_status(t_philo *philo);
void		mutex_int_set(int *elem, pthread_mutex_t *mutex_addr, int value);
int			mutex_int_get(int *elem, pthread_mutex_t *mutex_addr);
long		mutex_long_int_get(long *elem, pthread_mutex_t *mutex_addr);
void		clean_table(t_room *tab);
int			check_must_eat(t_philo *philo);

#endif
