/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/04 16:16:10 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void    custom_sleep(long int sleep_time)
{
    long current_time;
    
    current_time = ft_get_time_msec();
  //  printf("sleep time : [%li] ====== waiting : [%li]\n", sleep_time, ft_get_time_msec() - current_time);
    while(ft_get_time_msec() - current_time < sleep_time)
    {
        usleep(50);
    }
    return ;
}
