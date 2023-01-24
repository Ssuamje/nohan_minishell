/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/24 15:24:56 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int quotation_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING 
        || cur_status == LEX_QUOTATION
        || cur_status == LEX_NORMAL)
        add_char_to_buffer(get_char(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        add_char_to_buffer(get_char(c), lexer);
        lexer->status = cur_status;
        return (TRUE);
    }
    return (FALSE);
}

int apostrophe_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING 
        || cur_status == LEX_APOSTROPHE
        || cur_status == LEX_NORMAL)
        add_char_to_buffer(get_char(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        add_char_to_buffer(get_char(c), lexer);
        lexer->status = cur_status;
        return (TRUE);
    }
    return (FALSE);
}

int pipe_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_PIPE)
    {
        add_char_to_buffer(get_char(c), lexer);
        return (FALSE);
    }
    else
    {
        put_token_to_list(lexer, token_list);
        add_char_to_buffer(get_char(c), lexer);
        lexer->status = cur_status;
        return (TRUE);
    }
}

int env_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING
        || cur_status == LEX_ENV)
        add_char_to_buffer(get_char(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        add_char_to_buffer(get_char(c), lexer);
        lexer->status = cur_status;
        return (TRUE);
    }
    return (FALSE);
}

int lexical_analyze(t_list *token_list, char *c, t_lexer *lexer)
{
    if (lexer->status == LEX_NORMAL)
        return (normal_status(token_list, c, lexer));
    if (lexer->status == LEX_STRING)
        return (string_status(token_list, c, lexer));
    if (lexer->status == LEX_REDIRECT)
        return (redirect_status(token_list, c, lexer));
    if (lexer->status == LEX_QUOTATION)
        return (quotation_status(token_list, c, lexer));
    if (lexer->status == LEX_APOSTROPHE)
        return (apostrophe_status(token_list, c, lexer));
    if (lexer->status == LEX_PIPE)
        return (pipe_status(token_list, c, lexer));
    if (lexer->status == LEX_ENV)
        return (env_status(token_list, c, lexer));
    exit_error(ERR_STATUS);
    return (FALSE);
}