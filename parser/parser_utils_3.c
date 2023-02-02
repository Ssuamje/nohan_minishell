/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:38:36 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:15:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_process	*get_process(void)
{
	t_process	*to_return;

	to_return = malloc(sizeof(t_process));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->cmd = NULL;
	to_return->redir_in = ft_lstnew(NULL);
	to_return->redir_out = ft_lstnew(NULL);
	return (to_return);
}

t_parser	*get_parser(void)
{
	t_parser	*to_return;

	to_return = malloc(sizeof(t_parser));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->status = FALSE;
	to_return->flag_redir = FALSE;
	to_return->string = NULL;
	to_return->argv = ft_lstnew(NULL);
	return (to_return);
}

int	check_join_condition(t_token *next_token)
{
	return (next_token->is_seperated == FALSE
		&& (next_token->status == PAR_STRING || \
			next_token->status == PAR_QUOTATION || \
			next_token->status == PAR_APOSTROPHE || \
			next_token->status == PAR_ENV));
}

void	join_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	t_token	*next_token;

	tmp = tokens->next;
	while (tmp->next != NULL \
	&& tmp->next->content != NULL)
	{
		tmp_token = tmp->content;
		if (tmp_token->status == PAR_REDIRECT \
		|| tmp_token->status == PAR_PIPE)
		{
			tmp = tmp->next;
			continue ;
		}
		next_token = tmp->next->content;
		if (check_join_condition(next_token) != FALSE)
		{
			tmp_token->string = ft_join_and_free(tmp_token->string, \
												next_token->string);
			tmp = ft_lstpop(tokens, tmp->next, LST_LEFT);
			continue ;
		}
		tmp = tmp->next;
	}
}

int	parse_init(t_token *token, t_parser *parser)
{
	parser->status = token->status;
	if (token->status == PAR_PIPE)
		return (ERR_TRUE);
	if (token->status == PAR_REDIRECT)
	{
		parser->flag_redir = get_redir_flag(token->string);
		return (ERR_FALSE);
	}
	ft_lstadd_back(&(parser->argv), ft_lstnew(ft_strdup(token->string)));
	return (ERR_FALSE);
}
