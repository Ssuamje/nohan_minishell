/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:23:59 by sanan             #+#    #+#             */
/*   Updated: 2023/02/01 14:04:15 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
# define ENV_NONE -1
# define ENV_SYNTAX_ERROR 0
# define ENV_SUCCESS 1


int	get_env_idx(char *string)
{
	int idx;

	idx = 0;
	while (string[idx] != '\0'
		&& string[idx] != '$')
		idx++;
	if (string[idx] == '\0')
		return (-1);
	return (idx + 1);
}

char *get_env_string(char *input, int idx_env)
{
	int idx;
	char *to_return;

	idx = idx_env;
	while (input[idx] != '\0' \
		&& is_special(input[idx]) == FALSE)
		idx++;
	if (is_special(input[idx]) == TRUE)
		return (NULL);
	to_return = ft_strldup(&(input[idx_env]), (idx - idx_env));
	return (to_return);
}

// int	check_special_env(char *string)
// {
// 	return (is_in_charset(string[0], "?"));
// }

// int process_special_env(char *string)
// {

// }

void divide_interpret_part(char *string, char **after, int *to_find_len)
{
	int idx;

	idx = 0;
	while (string[idx] != ' ' \
		&& string[idx] != '\0' \
		&& is_special(string[idx]) == FALSE)
		idx++;
	if (string[idx] != '\0')
		*after = ft_strdup(&string[idx]);
	*to_find_len = idx;
}

void	set_env_to_string(t_environ *env, char **to_find)
{
	char *env_start_ptr;
	int env_len;

	free(*to_find);
	env_start_ptr = env->value;
	env_len = ft_strlen(env_start_ptr);
	*to_find = ft_strldup(env_start_ptr, env_len);
}

int	is_key_correct(char *key, char *to_find)
{
	return ((ft_strlen(key) == ft_strlen(to_find))
		&&	ft_strncmp(key, to_find, ft_strlen(key)) == 0);
}

int	interpret_env(t_list *envl, char **to_find)
{
	int			to_find_len;
	char		*after;
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = envl->next;
	while (tmp != NULL)
	{
		// if (check_special_env(*to_find) == TRUE)
		// 	return (process_special_env(*to_find));
		tmp_env = tmp->content;
		after = NULL;
		divide_interpret_part(*to_find, &after, &to_find_len);
		if (is_key_correct(tmp_env->key, *to_find))
		{
			set_env_to_string(tmp->content, to_find);
			*to_find = ft_join_and_free(*to_find, after);
			return (TRUE);
		}
		if (after && tmp->next->content != NULL)
			free(after);
		tmp = tmp->next;
	}
	free(*to_find);
	*to_find = ft_strdup("");
	if (after)
		*to_find = ft_join_and_free(*to_find, after);
	return(TRUE);
}

char	*join_env(char *input, int idx_env, char *env_string)
{
	int env_len;
	char *to_return;
	int	idx_dollar;

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

// int	process_env(char **envp, t_token *token)
// {
// 	int	idx_env;
// 	char *env_string;
// 	char *processed_string;

// 	idx_env = get_env_idx(token->string); // '$' 다음 인덱스, 없으면 -1
// 	if (idx_env == ENV_NONE)
// 		return (ENV_NONE);
// 	if (is_num(token->string[idx_env]) \
// 		|| token->string[idx_env] == '\0')
// 		return (ENV_SYNTAX_ERROR); // syntax error
// 	env_string = get_env_string(token->string, idx_env);
// 	printf("%s\n", env_string);
// 	interpret_env(envp, &env_string);
// 	processed_string = join_env(token->string, idx_env, env_string);
// 	free(env_string);
// 	free(token->string);
// 	token->string = processed_string;
// 	return (ENV_SUCCESS);
// }

void	print_split(char **split)
{
	int idx;

	idx = 0;
	// printf("split = %p\n", split);
	// pritnf("split[0] = %p\n", split[0]);
	if (split == NULL)
		return ;
	while (split[idx] != NULL)
	{
		printf("_%s_ ", split[idx]);
		idx++;
	}
	printf("\n");
}

int	count_dollar_sign(char *string)
{
	int idx;
	int	count;

	idx = 0;
	count = 0;
	while (string[idx])
		if (string[idx++] == '$')
			count++;
	return (count);
}

int count_env_string(char **split)
{
	int idx;

	idx = 0;
	while (split[idx] != NULL && split[idx][0] != '\0')
		idx++;
	return (idx);
}

void	free_split(char **split)
{
	int idx;

	idx = 0;
	while (split[idx] != NULL)
		free(split[idx++]);
	free(split);
}

char *skip_white_spaces(char **origin, int *idx_dollar)
{
	char	*skipped;

	skipped = *origin;
	*idx_dollar = 0;
	while (*skipped != '$')
	{
		skipped++;
		(*idx_dollar)++;
	}
	return (skipped + 1);
}

char **split_env_string(char *origin, char **processed_string)
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


int process_env(t_list *envl, t_token *token)
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
		processed_string = ft_strjoin(processed_string, env_splitted[idx]);
		idx++;
		free(tmp);
	}
	free(token->string);
	free_split(env_splitted);
	token->string = processed_string;
	return (ENV_SUCCESS);
}