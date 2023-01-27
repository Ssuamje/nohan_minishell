/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/27 21:57:59 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int parse(char **envp, char *input)
{
	t_list	*token_list;

	token_list = get_processed_token_list(envp, input);
	if (token_list == NULL)
	{
		free_token_list(&token_list);
		return (printf("syntax error occured!\n"));
	}
	print_token(token_list);
	//parser = get_parser();
	//processes = get_process_list();
	//parse_token_list(token_list, parser, processes);
	free_token_list(&token_list);
	//return (processes);
	return (0);
}
