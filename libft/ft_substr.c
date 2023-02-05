/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:50:14 by sanan             #+#    #+#             */
/*   Updated: 2023/01/21 19:31:11 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	src_len;
	size_t	length;

	if (!s)
		return (0);
	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		substr = ft_calloc(1, sizeof(char));
		return (substr);
	}
	if (len <= src_len - start)
		length = len;
	else
		length = src_len - start;
	substr = malloc(sizeof(char) * length + 1);
	if (substr == 0)
		return (0);
	ft_strlcpy(substr, (char *)&s[start], length + 1);
	return (substr);
}
