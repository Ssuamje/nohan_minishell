/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:14:40 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:45:14 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int	idx;

	idx = 0;
	while (set[idx])
	{
		if (set[idx] == c)
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	if (s1[0] == 0)
		return (ft_calloc(1, sizeof(char)));
	if (set[0] == 0)
		return (ft_strdup(s1));
	while (ft_isset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (start < end && ft_isset(s1[end], set))
		end--;
	result = malloc(sizeof(char) * (end - start + 1) + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, (char *)&s1[start], (end - start + 1) + 1);
	return (result);
}
