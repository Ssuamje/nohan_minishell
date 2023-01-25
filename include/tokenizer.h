/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:55:16 by sanan             #+#    #+#             */
/*   Updated: 2023/01/25 15:16:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "lexer.h"

typedef struct s_token{
	int		status;
	char	*string;
}	t_token;

typedef struct s_lexer	t_lexer;

t_list	*tokenize(char *input, t_lexer *lexer);
void	print_token(t_list *token_list);
t_token	*get_token(void);
void	put_token_to_list(t_lexer *lexer, t_list *token_list);
void	free_token_list(t_list **token_list);
char	*process_env(char **envp, char *string);
void	print_envp(char **envp); // need to delete
int 	is_num(char c);
int		is_alnum(char c);
int 	is_in_charset(char c, char *charset);
int 	is_special(char c);

#endif