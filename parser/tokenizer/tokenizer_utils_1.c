/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:23:59 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 18:03:15 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

int	process_env(t_list *envl, t_token *token)
{
	char	**env_splitted;
	int		idx;
	char	*processed_string;
	char	*tmp;

	if (count_dollar_sign(token->string) == 0
		|| token->status == LEX_APOSTROPHE)
		return (ENV_NONE);
	idx = 0;
	processed_string = NULL;
	env_splitted = split_env_string(token->string, &processed_string);
	if (env_splitted == NULL)
		return (ENV_SYNTAX_ERROR);
	while (env_splitted[idx] != NULL)
	{
		if (interpret_env(envl, &env_splitted[idx]) == FALSE)
			return (ENV_SYNTAX_ERROR);
		tmp = processed_string;
		if (env_splitted[idx] != NULL)
			processed_string = \
			ft_strjoin(processed_string, env_splitted[idx++]);
		free(tmp);
	}
	free(token->string);
	free_split(env_splitted);
	token->string = processed_string;
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
