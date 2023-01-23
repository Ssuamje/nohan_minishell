/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/23 20:58:12 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_lexer *get_lexer(void)
{
	t_lexer *to_return;

	to_return = malloc(sizeof(t_lexer));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
    to_return->env_buffer = NULL;
    to_return->str_buffer = NULL;
	to_return->status = LEX_NORMAL;
    return (to_return);
}


void    add_char_to_buffer(char *c, t_lexer *lexer)
{
    if (lexer->status == LEX_ENV)
        ft_lstadd_back(&(lexer->env_buffer), ft_lstnew(c));
    else
        ft_lstadd_back(&(lexer->str_buffer), ft_lstnew(c));
}

int need_to_tokenize(int prev, int cur)
{
    return (prev != cur);
}
// ['thisneedtobetoken']
// ["thisalsoneedtobetoken"]
// [asdfasfjkdjfkjkdf][<><><>][.][>]
//  [dsfjklxczvxzc.b/][|]

t_token *get_token(void)
{
    t_token *to_return;

    to_return = malloc(sizeof(t_token));
    if (to_return == NULL)
        exit_error(ERR_MALLOC);
    to_return->status = LEX_NORMAL;
    to_return->string = NULL;
    return (to_return);
}

char    *buffer_to_string(t_list *buffer)
{
    int     len;
    char    *string;
    t_list  *tmp;

    len = ft_lstsize(buffer);
    string = malloc(sizeof(char) * (len + 1));
    string[len] = '\0';
    tmp = buffer;
    len = 0;
    while (tmp != NULL)
    {
        string[len++] = *((char *)tmp->content);
        tmp = tmp->next;
    }
    return (string);
}

void    flush_buffer(t_lexer *lexer)
{
    ft_lstclear(&(lexer->env_buffer), free);
    ft_lstclear(&(lexer->str_buffer), free);
}

char    *get_processed_string(t_lexer *lexer)
{
    char    *env_string;
    char    *string;
    char    *to_return;

    env_string = NULL;
    to_return = NULL;
    if (lexer->status != LEX_APOSTROPHE)
        env_string = buffer_to_string(lexer->env_buffer);
    string = buffer_to_string(lexer->str_buffer);
    to_return = ft_strjoin(string, env_string);
    if (env_string)
        free(env_string);
    free(string);
    flush_buffer(lexer);
    return (to_return);
}

void    put_token_to_list(t_lexer *lexer, t_list *token_list)
{
    t_token *token;
    
    token = get_token();
    token->status = lexer->status;
    token->string = get_processed_string(lexer);
    token->string = ft_strtrim(token->string, " \t");
    ft_lstadd_back(&token_list, ft_lstnew(token));
}

char    *char_ptr(char *ptr)
{
    char *to_return;

    to_return = malloc(sizeof(char));
    if (to_return == NULL)
        exit_error(ERR_MALLOC);
    *to_return = *ptr;
    return (to_return);
}

int    get_status(char c)
{
    if (c == ' ' || c == '\t')
        return (LEX_NORMAL);
    else if (c == '\"')
        return (LEX_QUOTATION);
    else if (c == '\'')
        return (LEX_APOSTROPHE);
    else if (c == '<' || c == '>')
        return (LEX_REDIRECT);
    else if (c == '|')
        return (LEX_PIPE);
    else if (c == '$')
        return (LEX_ENV);
    else
        return (LEX_STRING);
}

int normal_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    (void)token_list;
    if (*c == ' ' || *c == '\t')
        return (FALSE);
    cur_status = get_status(*c);
    lexer->status = cur_status;
    add_char_to_buffer(char_ptr(c), lexer);
    return (TRUE);
}

int string_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status != LEX_STRING)
    {
        put_token_to_list(lexer, token_list);
        lexer->status = cur_status;
        add_char_to_buffer(char_ptr(c), lexer);
        return (TRUE);
    }
    add_char_to_buffer(char_ptr(c), lexer);
    lexer->status = cur_status;
    return (TRUE);
}

int redirect_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status != LEX_REDIRECT)
    {
        put_token_to_list(lexer, token_list);
        lexer->status = cur_status;
        add_char_to_buffer(char_ptr(c), lexer);
        return (TRUE);
    }
    add_char_to_buffer(char_ptr(c), lexer);
    lexer->status = cur_status;
    return (TRUE);
}

int quotation_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING 
        || cur_status == LEX_QUOTATION
        || cur_status == LEX_NORMAL)
        add_char_to_buffer(char_ptr(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        lexer->status = cur_status;
        add_char_to_buffer(char_ptr(c), lexer);
        return (TRUE);
    }
    return (FALSE);
}

int apostrophe_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING 
        || cur_status == LEX_APOSTROPHE)
        add_char_to_buffer(char_ptr(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        lexer->status = cur_status;
        add_char_to_buffer(char_ptr(c), lexer);
        return (TRUE);
    }
    return (FALSE);
}

int pipe_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    put_token_to_list(lexer, token_list);
    lexer->status = cur_status;
    add_char_to_buffer(char_ptr(c), lexer);
    return (TRUE);
}

int env_status(t_list *token_list, char *c, t_lexer *lexer)
{
    int cur_status;

    cur_status = get_status(*c);
    if (cur_status == LEX_STRING)
        add_char_to_buffer(char_ptr(c), lexer);
    else
    {
        put_token_to_list(lexer, token_list);
        lexer->status = cur_status;
        add_char_to_buffer(char_ptr(c), lexer);
        return (TRUE);
    }
    return (FALSE);
}


int set_status(t_list *token_list, char *c, t_lexer *lexer)
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

t_list	*tokenize(char *input, t_lexer *lexer)
{                                   
	int     idx;
    t_list *token_list;

	idx = 0;
    token_list = ft_lstnew(NULL);
	while (input[idx] != '\0')
	{
        set_status(token_list, &input[idx], lexer);
		idx++;
	}
    if (lexer->status != LEX_NORMAL)
        put_token_to_list(lexer, token_list);
    return (token_list);
}

void    print_token(t_list *token_list)
{
    t_list *tmp;
    t_token *token;

    tmp = token_list->next;
    while (tmp != NULL)
    {
        token = tmp->content;
        if (token->status == LEX_STRING)
            printf("{status : STRING,\n");
        if (token->status == LEX_NORMAL)
            printf("{status : NORMAL,\n");
        if (token->status == LEX_APOSTROPHE)
            printf("{status : APOSTROPHE,\n");
        if (token->status == LEX_ENV)
            printf("{status : ENV,\n");
        if (token->status == LEX_PIPE)
            printf("{status : PIPE,\n");
        if (token->status == LEX_QUOTATION)
            printf("{status : QUOTATION,\n");
        if (token->status == LEX_REDIRECT)
            printf("{status : REDIRECT,\n");
        printf(" string : _%s_}\n\n", token->string);
        tmp = tmp->next;
    }
}

int main(int ac, char **av)
{
	t_lexer *lexer;
    t_list  *token_list;

	if (ac != 2)
		return (1);
	lexer = get_lexer();
	token_list = tokenize(av[1], lexer);
    print_token(token_list);
    system("leaks a.out");
	return (0);
}