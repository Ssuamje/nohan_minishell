/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:38:13 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 19:44:11 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	is_token_not_env_not_has_special(t_token *token)
{
	return (is_in_charset(token->string[0], "~!@#$%^&*()_+`-=[]{}\\|/?><,.")
		&& (token->status != PAR_ENV));
}

int	check_first_arg(t_token *token)
{
	return (token->status != PAR_PIPE
		&& token->status != PAR_REDIRECT
		&& is_token_not_env_not_has_special(token) == FALSE);
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
