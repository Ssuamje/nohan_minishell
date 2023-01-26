/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/26 19:48:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	check_leaks(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lexer;
	t_list	*token_list;

	atexit(check_leaks);
	if (ac != 2)
		return (1);
	lexer = get_lexer();
	token_list = tokenize(av[1], lexer);
	print_token(token_list);
	//parser = get_parser();
	//processes = get_process_list();
	//parse_token_list(token_list, parser, processes);
	free_token_list(&token_list);
	free(lexer);
	//return (processes);
	return (0);
}

//  trim 한번만 하고 quotation, apostrophe 에러처리
//  여러개 이어진 환경변수 해석
//  컨디션에 따라 환경변수 해석