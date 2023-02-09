/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:25:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:30:43 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	is_in_str(char c, char *str)
{
	int	idx;

	if (str == NULL)
		return (FALSE);
	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == c)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}
