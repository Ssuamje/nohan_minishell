/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:46:40 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:21:46 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*to;
	unsigned char	*from;

	i = 0;
	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	if (to == 0 && from == 0)
		return (dst);
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return ((void *)to);
}
