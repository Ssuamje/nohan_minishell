/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:55:16 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 16:53:06 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "lexer.h"
# include "envl.h"

typedef struct s_token{
	int		status;
	int		is_seperated;
	char	*string;
}	t_token;

typedef struct s_lexer	t_lexer;

t_list	*tokenize(char *input, t_lexer *lexer);
t_token	*get_token(void);
void	put_token_to_list(t_lexer *lexer, t_list *tokens);
void	free_tokens(t_list **tokens);
int		process_env(t_list *envl, t_token *token);
char	**split_env_string(char *origin, char **processed_string);
int		get_env_idx(char *string);
char	*get_env_string(char *input, int idx_env);
void	divide_interpret_part(char **to_find, char **after);
char	*remove_quote_apost(char *string, char c, int *flag);
void	check_set_token_properties(t_token *token);
void	lstrip_once(char **string);
void	check_string_condition(t_token *token);
int		process_tokens_env(t_list *envl, t_list *tokens);
int		is_num(char c);
int		is_alnum(char c);
int		is_in_charset(char c, char *charset);
int		is_special(char c);
int		count_char(char *string, char c);
void	free_lexer(t_lexer *lexer);
t_list	*get_processed_tokens(t_list *envl, char *input);
int		count_env_string(char **split);
void	free_split(char **split);
char	*skip_white_spaces(char **origin, int *idx_dollar);
void	set_env_to_string(t_environ *env, char **to_find);
int		is_key_correct(char *key, char *to_find);
int		interpret_env(t_list *envl, char **to_find);
char	*join_env(char *input, int idx_env, char *env_string);
int		count_dollar_sign(char *string);
void	free_double(void *p1, void *p2);
int		is_dont_need_interpret(char *string);
int		process_env_split_and_join(char **env_splitted, \
								t_list *envl, char **processed_string);
char	**split_env_with_dollar(char *str);

#endif