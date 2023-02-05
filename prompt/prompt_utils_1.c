/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:18 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 17:18:35 by hyungnoh         ###   ########.fr       */
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

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
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
