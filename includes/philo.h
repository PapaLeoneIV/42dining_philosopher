/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:17:11 by rileone           #+#    #+#             */
/*   Updated: 2024/03/18 11:53:57 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf.h"
# include <pthread.h>

typedef struct s_philo
{
    int n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_must_eat;
    long int timestamp;
} t_philo;


int ft_init_var(t_philo *var, char **argv);

#endif