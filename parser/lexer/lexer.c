/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 22:05:18 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../error/error.h"

t_token *init_token_list(void)
{
	t_token *to_return;

	to_return = malloc(sizeof(t_token));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->status = LEX_NORMAL;
	to_return->string = NULL;
	to_return->next = NULL;
	return (to_return);
}

int main(int ac, char **av)
{
	char *input;
	
    if (ac != 2)
        return (1);
	input = av[1];
	lexical_analyze(input, token_list);
	return (0);
}