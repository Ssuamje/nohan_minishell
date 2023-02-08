/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/02/08 14:21:55 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	*free_token_return_null(t_list **tokens, char *msg)
{
	free_tokens(tokens);
	printf("%s", msg);
	set_exit_code(g_global->g_envl, 258);
	return (NULL);
}

void	*free_process_return_null(t_list **tokens, t_list *processes,
								t_parser *parser)
{
	free_token_return_null(tokens, "parse error occurred!\n");
	free_parser(&parser);
	free_process_list(processes);
	return (NULL);
}

t_list	*parse(t_list *envl, char *input)
{
	t_list		*tokens;
	t_parser	*parser;
	t_list		*processes;

	tokens = get_processed_tokens(envl, input);
	if (tokens == NULL)
		return (free_token_return_null(&tokens, \
									"AengMuShell: invaliad env!\n"));
	if (check_syntax(tokens) == ERR_TRUE)
		return (free_token_return_null(&tokens, \
									"AengMuShell: syntax error occurred!\n"));
	join_tokens(tokens);
	parser = get_parser();
	processes = ft_lstnew(NULL);
	if (parse_tokens(tokens, processes, parser) == ERR_TRUE)
		return (free_process_return_null(&tokens, processes, parser));
	free_tokens(&tokens);
	free_parser(&parser);
	return (processes);
}
