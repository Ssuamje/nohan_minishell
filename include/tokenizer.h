/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:55:16 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 17:36:43 by hyungnoh         ###   ########.fr       */
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
int 	is_num(char c);
int		is_alnum(char c);
int 	is_in_charset(char c, char *charset);
int 	is_special(char c);
int		process_tokens_env(t_list *envl, t_list *tokens);
int		count_char(char *string, char c);
void	free_split(char **split);

#endif