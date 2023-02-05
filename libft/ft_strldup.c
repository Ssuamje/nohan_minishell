/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:57:34 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 19:44:18 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strldup(char *src, int len)
{
	char	*dest;
	int		src_len;
	int		dest_len;
	int		idx;

	if (src == NULL)
		return (NULL);
	idx = 0;
	src_len = ft_strlen(src);
	if (src_len > len)
		dest_len = len;
	else
		dest_len = src_len;
	dest = malloc(sizeof(char) * (dest_len + 1));
	while (idx < dest_len && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}
