/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:32:11 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 18:41:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../include/parser.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

int	interpret_buffer_env(char **buffer)
{
	char	**env_splitted;
	int		idx;
	char	*processed_string;
	char	*tmp;

	idx = 0;
	env_splitted = split_env_string(*buffer, &processed_string);
	while (env_splitted[idx] != NULL)
	{
		if (interpret_env(g_envl, &env_splitted[idx]) == FALSE)
			return (FALSE);
		tmp = processed_string;
		if (env_splitted[idx] != NULL)
			processed_string = \
			ft_strjoin(processed_string, env_splitted[idx++]);
		free(tmp);
	}
	free(*buffer);
	free_split(env_splitted);
	*buffer = processed_string;
	return (TRUE);
}
