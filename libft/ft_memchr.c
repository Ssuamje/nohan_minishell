/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:10:31 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:21:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*to_find;

	i = 0;
	to_find = (unsigned char *)s;
	while (i < n)
	{
		if (to_find[i] == (unsigned char)c)
			return ((void *)&to_find[i]);
		i++;
	}
	return (0);
}
