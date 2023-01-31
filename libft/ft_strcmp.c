/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:45:08 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 13:46:43 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_strcmp(char *s1, char *s2)
{
	int idx;

	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	idx = 0;
	while (s1[idx])
	{
		if (s1[idx] != s2[idx])
			return (0);
		idx++;
	}
	return (1);
}