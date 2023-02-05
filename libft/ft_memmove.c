/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:50:25 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:21:46 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*from;
	unsigned char		*to;

	from = (unsigned char *)src;
	to = (unsigned char *)dst;
	if (len == 0)
		return (dst);
	if (from < to)
	{
		i = len + 1;
		while (--i > 0)
			to[i - 1] = from[i - 1];
		return ((void *)to);
	}
	if (from > to)
	{
		i = -1;
		while (++i < len)
			to[i] = from[i];
		return ((void *)to);
	}
	return ((void *)to);
}
