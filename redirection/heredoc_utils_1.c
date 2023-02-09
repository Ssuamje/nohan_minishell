/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:32:11 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 10:52:29 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

void	divide_interpret_part_heredoc(char **to_find, char **after)
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

int	interpret_env_heredoc(t_list *envl, char **to_find)
{
	char		*after;
	char		*tmp;

	if ((count_dollar_sign(*to_find) < 1 \
	|| ft_strcmp(*to_find, "$") == TRUE) \
	|| is_special((*to_find)[1]) == TRUE)
		return (TRUE);
	after = NULL;
	tmp = *to_find;
	*to_find = ft_strdup(*to_find + 1);
	free(tmp);
	divide_interpret_part(to_find, &after);
	tmp = *to_find;
	*to_find = ft_join_and_free(get_value_by_key(envl, *to_find), after);
	free(tmp);
	return (TRUE);
}

int	interpret_buffer_env(char **buffer)
{
	char	**env_splitted;
	int		idx;
	char	*processed_string;
	char	*tmp;

	idx = 0;
	processed_string = NULL;
	env_splitted = split_env_with_dollar(*buffer);
	while (env_splitted[idx] != NULL)
	{
		if (interpret_env_heredoc(\
		g_global->g_envl, &env_splitted[idx]) == FALSE)
			return (FALSE);
		tmp = processed_string;
		processed_string = ft_strjoin(processed_string, env_splitted[idx++]);
		free(tmp);
	}
	free(*buffer);
	free_split(env_splitted);
	*buffer = processed_string;
	return (TRUE);
}
