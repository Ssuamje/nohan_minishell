/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:33 by sanan             #+#    #+#             */
/*   Updated: 2022/11/11 05:22:24 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == (char)c)
			return ((char *)(s + idx));
		idx++;
	}
	if (s[idx] == (char)c)
		return ((char *)(s + idx));
	return (0);
}
