/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:31:26 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:16:02 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	check_apost_quote_flag(char *c, t_lexer *lexer)
{
	if (*c == '\'')
	{
		if (lexer->apost_flag == TRUE)
			lexer->apost_flag = FALSE;
		else if (lexer->quote_flag == FALSE)
			lexer->apost_flag = TRUE;
	}
	if (*c == '\"')
	{
		if (lexer->quote_flag == TRUE)
			lexer->quote_flag = FALSE;
		else if (lexer->apost_flag == FALSE)
			lexer->quote_flag = TRUE;
	}
}
