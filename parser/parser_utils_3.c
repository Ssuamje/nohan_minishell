/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:38:36 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:37:37 by sanan            ###   ########.fr       */
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

char	*join_env_token(char *cur, char *after)
{
	char	*to_return;

	if (ft_strlen(cur) > 1)
		to_return = ft_join_and_free(cur, after);
	else
	{
		free(cur);
		to_return = ft_join_and_free(NULL, after);
	}
	return (to_return);
}

void	join_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*next;

	tmp = tokens->next;
	while (tmp->next != NULL && tmp->next->content != NULL)
	{
		token = tmp->content;
		if (token->status == PAR_REDIRECT || token->status == PAR_PIPE)
		{
			tmp = tmp->next;
			continue ;
		}
		next = tmp->next->content;
		if (check_join_condition(next) == TRUE)
		{
			if (token->status == PAR_ENV)
				token->string = join_env_token(token->string, next->string);
			else
				token->string = ft_join_and_free(token->string, next->string);
			tmp = ft_lstpop(tokens, tmp->next, LST_LEFT);
			continue ;
		}
		tmp = tmp->next;
	}
}
