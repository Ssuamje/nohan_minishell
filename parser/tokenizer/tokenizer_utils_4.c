/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:26:19 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:32:07 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

void	free_lexer(t_lexer *lexer)
{
	ft_lstclear(&(lexer->env_buffer), free);
	ft_lstclear(&(lexer->str_buffer), free);
	free(lexer);
}

t_list	*get_processed_tokens(t_list *envl, char *input)
{
	t_lexer	*lexer;
	t_list	*tokens;

	lexer = get_lexer();
	tokens = tokenize(input, lexer);
	process_tokens_env(envl, tokens);
	free_lexer(lexer);
	return (tokens);
}

int	count_env_string(char **split)
{
	int	idx;

	if (split == NULL)
		return (0);
	idx = 0;
	while (split[idx] != NULL && split[idx][0] != '\0')
		idx++;
	return (idx);
}

void	free_split(char **split)
{
	int	idx;

	if (split == NULL)
		return ;
	idx = 0;
	while (split[idx] != NULL)
		free(split[idx++]);
	free(split);
}

char	*skip_white_spaces(char **origin, int *idx_dollar)
{
	char	*skipped;

	skipped = *origin;
	*idx_dollar = 0;
	while (*skipped != '$' && *skipped != '\0')
	{
		(*idx_dollar)++;
		skipped++;
	}
	return (skipped + 1);
}
