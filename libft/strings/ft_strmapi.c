/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <riccardo.leone@student.42fir      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:23:13 by rileone           #+#    #+#             */
/*   Updated: 2024/04/02 15:23:18 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	slen;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	str = malloc(sizeof(char) * slen + 1);
	if (!(str))
		return (0);
	i = 0;
	if (s && f)
	{
		while (i < slen)
		{
			str[i] = f(i, s[i]);
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
