/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:58:09 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:22:35 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(dest) >= size)
		return (ft_strlen(src) + size);
	i = ft_strlen(dest);
	j = 0;
	len_dest = ft_strlen(dest);
	while (src[j] && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (len_dest + ft_strlen(src));
}
