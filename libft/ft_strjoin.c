/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:43:38 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:27:43 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	result = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, (char *)s1, len_s1 + 1);
	ft_strlcpy(&result[len_s1], (char *)s2, len_s2 + 1);
	return (result);
}
