/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/29 21:39:20 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_process	*get_process(void)
{
	t_process	*to_return;

	to_return = malloc(sizeof(t_process));
	to_return->cmd = NULL;
	to_return->redir_in = NULL;
	to_return->redir_out = NULL;
	return (to_return);
}

// void	parse_tokens(t_list *tokens, t_list *processes)
// {
	
// }

t_list *parse(char **envp, char *input)
{
	t_list		*tokens;
	t_list		*processes;

	tokens = get_processed_tokens(envp, input);
	if (tokens == NULL)
	{
		free_tokens(&tokens);
		printf("syntax error occured!\n");
		return (NULL);
	}
	print_token(tokens);
	processes = ft_lstnew(NULL);
	// parse_tokens(tokens, processes);
	free_tokens(&tokens);
	return (processes);
}
