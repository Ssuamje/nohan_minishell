/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:58:06 by hyungnoh          #+#    #+#             */
/*   Updated: 2022/11/21 15:54:12 by hyungnoh         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	else
	{
		buffer = malloc(size * count);
		if (buffer == 0)
			return (0);
		ft_bzero(buffer, size * count);
		return (buffer);
	}
}
