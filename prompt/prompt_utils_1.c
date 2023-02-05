/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:18 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 20:27:01 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"

int	get_len(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int	is_string_only_white_spaces(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (is_in_charset(str[idx], " \t") == FALSE)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

int	is_input_empty(char *input)
{
	if (get_len(input) == 0 ||is_string_only_white_spaces(input))
	{
		free(input);
		return (TRUE);
	}
	return (FALSE);
}
