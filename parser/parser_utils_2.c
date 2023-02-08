/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:38:13 by sanan             #+#    #+#             */
/*   Updated: 2023/02/08 14:07:13 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	is_token_not_env_not_has_special(t_token *token)
{
	if (token->string == NULL)
		return (FALSE);
	return (is_in_charset(token->string[0], "`!#%^&*(){}\\|\'\";:")
		&& (token->status != PAR_ENV)
		&& (token->status != PAR_APOSTROPHE)
		&& (token->status != PAR_QUOTATION));
}

int	check_first_arg(t_token *token)
{
	return (token->status != PAR_PIPE
		&& is_token_not_env_not_has_special(token) == FALSE);
}

int	check_args_first(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;

	tmp = tokens->next;
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
		if (check_first_arg(tmp_token) == FALSE)
			return (ERR_TRUE);
		tmp = tmp->next;
	}
	return (ERR_FALSE);
}

int	get_redir_flag(char *redir)
{
	if (ft_strcmp(redir, "<") == TRUE)
		return (IN_TRUNC);
	if (ft_strcmp(redir, "<<") == TRUE)
		return (IN_APPEND);
	if (ft_strcmp(redir, ">") == TRUE)
		return (OUT_TRUNC);
	if (ft_strcmp(redir, ">>") == TRUE)
		return (OUT_APPEND);
	return (FALSE);
}

void	free_parser(t_parser **parser)
{
	ft_lstclear(&((*parser)->argv), free);
	if ((*parser)->string)
		free((*parser)->string);
	free(*parser);
}
