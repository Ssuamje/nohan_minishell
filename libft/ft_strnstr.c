/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:47:13 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:22:49 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (needle[0] == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && len - i >= ft_strlen(needle))
	{
		if (!(ft_memcmp((char *)&haystack[i], needle, ft_strlen(needle))))
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
