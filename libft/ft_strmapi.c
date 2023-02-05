/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:16:07 by sanan             #+#    #+#             */
/*   Updated: 2022/11/10 23:31:22 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		idx;
	char	*result;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	idx = 0;
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	result[len] = 0;
	while (idx < len)
	{
		result[idx] = f(idx, s[idx]);
		idx++;
	}
	return (result);
}
