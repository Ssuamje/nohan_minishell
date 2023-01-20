/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:12:58 by hyungnoh          #+#    #+#             */
/*   Updated: 2022/11/14 11:05:57 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*buffer;
	char	ch;
	size_t	cnt;

	ch = c;
	cnt = 0;
	while (*s != 0)
	{
		if (*s == ch)
		{
			buffer = (char *)s;
			cnt++;
		}
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	if (cnt > 0)
		return (buffer);
	return (0);
}
