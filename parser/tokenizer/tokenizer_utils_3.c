/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:11:23 by sanan             #+#    #+#             */
/*   Updated: 2023/01/25 15:55:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

int is_num(char c)
{
	return ('0' <= c && c <= '9');
}

int	is_alnum(char c)
{
	return (('0' <= c && c <= '9') \
			|| ('a' <= c && c <= 'z') \
			|| ('A' <= c && c <= 'Z'));
}

int is_in_charset(char c, char *charset)
{
	int idx;

	idx = 0;
	while (charset[idx])
	{
		if (c == charset[idx])
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

int is_special(char c)
{
	return (is_in_charset(c, "!@#$%^&*()_-+={[}]\\|:;/?.,<>~`"));
}
