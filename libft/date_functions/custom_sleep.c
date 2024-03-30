/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:50:28 by rileone           #+#    #+#             */
/*   Updated: 2024/03/30 20:03:51 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    custom_sleep(int sleep_time)
{
    long current_time;
    
    current_time = ft_get_time_msec();
    while(42)
    {
        if(ft_get_time_msec() - current_time < sleep_time * 1000)
            return ;        
    }
    return ;
}