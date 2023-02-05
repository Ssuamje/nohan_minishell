/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:08:19 by sanan             #+#    #+#             */
/*   Updated: 2022/11/10 22:25:57 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_sep(char c_in_str, char sep)
{
	return (c_in_str == sep);
}

static int	count_chunk(const char *str, char c)
{
	int	i;
	int	chunk;

	i = 0;
	chunk = 0;
	while (is_sep(str[i], c) && str[i])
		i++;
	while (str[i])
	{
		while (!is_sep(str[i], c) && str[i])
			i++;
		while (is_sep(str[i], c) && str[i])
			i++;
		chunk++;
	}
	return (chunk);
}

static char	*paste(char *dest, const char *str, char c, int *idx)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (is_sep(str[*idx], c))
		*idx = *idx + 1;
	while (!is_sep(str[*idx + j], c) && str[*idx + j])
		j++;
	len = j;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, (char *)&str[*idx], len + 1);
	*idx = *idx + j;
	return (dest);
}

char	**ft_split(const char *str, char c)
{
	char	**split;
	int		chunk;
	int		idx;
	int		i;

	chunk = count_chunk(str, c);
	split = (char **)malloc(sizeof(char *) * (chunk + 1));
	if (!split)
		return (0);
	idx = 0;
	i = 0;
	while (i < chunk)
	{
		split[i] = paste(split[i], str, c, &idx);
		if (!split[i])
		{
			while (--i >= 0)
				free(split[i]);
			free(split);
			return (0);
		}
		i++;
	}
	split[chunk] = 0;
	return (split);
}
