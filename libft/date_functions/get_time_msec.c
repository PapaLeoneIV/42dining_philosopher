/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_msec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:13:45 by rileone           #+#    #+#             */
/*   Updated: 2024/03/19 15:17:01 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long ft_get_time_msec(void)
{
    struct timeval current_time;
    long time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    if (!time_in_ms)
        return (0);
    return (time_in_ms);
}