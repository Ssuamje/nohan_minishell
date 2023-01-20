/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:14:11 by hyungnoh          #+#    #+#             */
/*   Updated: 2022/11/17 18:41:17 by hyungnoh         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*new;

	len = ft_strlen(s1);
	new = malloc(sizeof(char) * len + 1);
	if (new == 0)
		return (0);
	ft_memcpy(new, s1, len);
	new[len] = 0;
	return (new);
}
