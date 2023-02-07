/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:28:26 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 14:07:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

int	is_dont_need_interpret(t_token *token)
{
	if (token->status == LEX_APOSTROPHE
		|| count_dollar_sign(token->string) == 0)
		return (TRUE);
	if ((token->string[0] == '$') && \
			((token->string[1] == '\0') || \
			(is_special(token->string[1]) == TRUE) || \
			(ft_isdigit(token->string[1]) == TRUE)))
		return (TRUE);
	return (FALSE);
}

int	process_env_split_and_join(char **env_splitted, \
								t_list *envl, char **processed_string)
{
	int		idx;
	char	*tmp;

	idx = 0;
	if (env_splitted == NULL)
		return (ENV_SYNTAX_ERROR);
	while (env_splitted[idx] != NULL)
	{
		if (interpret_env(envl, &env_splitted[idx]) == FALSE)
			return (ENV_SYNTAX_ERROR);
		tmp = *processed_string;
		if (env_splitted[idx] != NULL)
		{
			*processed_string = \
			ft_strjoin(*processed_string, env_splitted[idx++]);
			free(tmp);
		}
	}
	return (ENV_SUCCESS);
}
