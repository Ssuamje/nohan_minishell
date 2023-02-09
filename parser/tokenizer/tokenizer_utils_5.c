/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:28:26 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:31:36 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

void	set_env_to_string(t_environ *env, char **to_find)
{
	free(*to_find);
	*to_find = ft_strdup(env->value);
}

int	is_key_correct(char *key, char *to_find)
{
	return ((ft_strlen(key) == ft_strlen(to_find))
		&&ft_strncmp(key, to_find, ft_strlen(key)) == 0);
}

int	interpret_env(t_list *envl, char **to_find)
{
	char		*after;
	char		*tmp;

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

char	*join_env(char *input, int idx_env, char *env_string)
{
	int		env_len;
	char	*to_return;
	int		idx_dollar;

	env_len = ft_strlen(env_string);
	idx_dollar = idx_env - 1;
	to_return = malloc(sizeof(char) * (idx_dollar + env_len + 1));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return[idx_dollar + env_len] = '\0';
	ft_memcpy(to_return, input, idx_dollar + 1);
	ft_memcpy(&to_return[idx_dollar], env_string, env_len + 1);
	return (to_return);
}

int	count_dollar_sign(char *string)
{
	int	idx;
	int	count;

	if (string == NULL)
		return (0);
	idx = 0;
	count = 0;
	while (string[idx])
		if (string[idx++] == '$')
			count++;
	return (count);
}
