/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:17:09 by sanan             #+#    #+#             */
/*   Updated: 2023/01/23 22:34:16 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft.h"
#include "error.h"
#include "bool.h"
#include "tokenizer.h"
#include <stdlib.h>

typedef struct s_lexer{
	int     status;
	t_list  *env_buffer;
	t_list  *str_buffer;
}   t_lexer;

enum e_lexer_status{
	LEX_NORMAL,
	LEX_STRING,
	LEX_REDIRECT,
	LEX_QUOTATION,
	LEX_APOSTROPHE,
	LEX_PIPE,
	LEX_ENV,
};

t_lexer *get_lexer(void);
void    add_char_to_buffer(char *c, t_lexer *lexer);
char    *buffer_to_string(t_list *buffer);
void    flush_buffer(t_lexer *lexer);
char    *get_processed_string(t_lexer *lexer);
char    *get_char(char *ptr);
int     get_status(char c);
int     normal_status(t_list *token_list, char *c, t_lexer *lexer);
int     string_status(t_list *token_list, char *c, t_lexer *lexer);
int     redirect_status(t_list *token_list, char *c, t_lexer *lexer);
int     quotation_status(t_list *token_list, char *c, t_lexer *lexer);
int     apostrophe_status(t_list *token_list, char *c, t_lexer *lexer);
int     pipe_status(t_list *token_list, char *c, t_lexer *lexer);
int     env_status(t_list *token_list, char *c, t_lexer *lexer);
int     lexical_analyze(t_list *token_list, char *c, t_lexer *lexer);

#endif