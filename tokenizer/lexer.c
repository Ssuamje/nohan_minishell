/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/17 19:55:23 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc *collector;

t_token *init_token_list(void)
{
	t_token *to_return;

	to_return = malloc(sizeof(t_token));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->status = NORMAL;
	to_return->string = NULL;
	to_return->next = NULL;
	return (to_return);
}

int main(int ac, char **av)
{
	char *input;
	t_token *token_list;
	
	(void)ac;
	(void)input;
	collector = get_garbage_collector();
	input = av[1]; // 반드시 av1만 받는 형식으로 테스팅 중
	token_list = init_token_list();
	add_garbage(collector, (void **)&token_list, GBG_TOKEN_LIST);
	sweep_all_garbages(&collector);
	// lexical_analyze(input, token_list);
	return (1);
}