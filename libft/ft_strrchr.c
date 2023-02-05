/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:50 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 00:24:42 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		idx;
	int		flag;
	char	*target;

	idx = 0;
	flag = 0;
	while (s[idx])
	{
		if (s[idx] == (char)c)
		{
			flag = 1;
			target = (char *)(s + idx);
		}
		idx++;
	}
	if (s[idx] == (char)c)
		return ((char *)&s[idx]);
	if (flag == 1)
		return (target);
	else
		return (0);
}
