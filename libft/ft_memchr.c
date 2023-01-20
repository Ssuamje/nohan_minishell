/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:54 by hyungnoh          #+#    #+#             */
/*   Updated: 2022/11/14 10:55:25 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	size_t				cnt;
	unsigned char		*buffer;

	i = 0;
	cnt = 0;
	buffer = (unsigned char *)s;
	while (i < n)
	{
		if (*buffer == (unsigned char)c)
		{
			cnt++;
			break ;
		}
		i++;
		buffer++;
	}
	if (cnt > 0)
		return ((void *)buffer);
	return (0);
}
