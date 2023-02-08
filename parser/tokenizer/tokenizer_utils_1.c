/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:23:59 by sanan             #+#    #+#             */
/*   Updated: 2023/02/08 14:36:50 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

int	process_env(t_list *envl, t_token *token)
{
	char	**env_splitted;
	char	*processed_string;

	if (token->status == LEX_APOSTROPHE \
	|| count_dollar_sign(token->string) == 0)
		return (ENV_NONE);
	processed_string = NULL;
	env_splitted = split_env_with_dollar(token->string);
	if (process_env_split_and_join(env_splitted, envl, &processed_string)
		== ENV_SYNTAX_ERROR)
		return (ENV_SYNTAX_ERROR);
	free(token->string);
	free_split(env_splitted);
	token->string = processed_string;
	if (token->string[0] == '\0')
	{
		free(token->string);
		token->string = NULL;
	}
	return (ENV_SUCCESS);
}

char	**split_env_string(char *origin, char **processed_string)
{
	int		count_env_split;
	int		idx_dollar;
	char	*string_to_split;
	char	**env_splitted;

	string_to_split = skip_white_spaces(&origin, &idx_dollar);
	if (string_to_split[0] == '\0'
		|| is_special(string_to_split[0]) == TRUE)
		return (NULL);
	*processed_string = ft_strldup(origin, idx_dollar);
	count_env_split = count_dollar_sign(origin);
	env_splitted = ft_split(string_to_split, '$');
	if (env_splitted == NULL)
		return (ft_free_and_return(*processed_string, NULL));
	if (count_env_split != count_env_string(env_splitted))
	{
		free_split(env_splitted);
		return (ft_free_and_return(*processed_string, NULL));
	}
	return (env_splitted);
}

int	get_env_idx(char *string)
{
	int	idx;

	idx = 0;
	while (string[idx] != '\0'
		&& string[idx] != '$')
		idx++;
	if (string[idx] == '\0')
		return (-1);
	return (idx + 1);
}

char	*get_env_string(char *input, int idx_env)
{
	int		idx;
	char	*to_return;

	idx = idx_env;
	while (input[idx] != '\0' \
		&& is_special(input[idx]) == FALSE)
		idx++;
	if (is_special(input[idx]) == TRUE)
		return (NULL);
	to_return = ft_strldup(&(input[idx_env]), (idx - idx_env));
	return (to_return);
}

void	divide_interpret_part(char **to_find, char **after)
{
	int		idx;
	char	*tmp;
	char	*env_key;

	idx = 0;
	env_key = *to_find;
	while (env_key[idx] != '\0' \
		&& env_key[idx] != ' ' \
		&& env_key[idx] != '\t' \
		&& is_special(env_key[idx]) == FALSE)
		idx++;
	*after = ft_strldup(&(env_key[idx]), ft_strlen(env_key) - idx);
	tmp = ft_strldup(env_key, idx);
	free(*to_find);
	*to_find = tmp;
}
