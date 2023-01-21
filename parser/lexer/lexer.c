/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/21 20:33:49 by sanan            ###   ########.fr       */
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

void    get_status(char c, t_lexer *lexer)
{
    if (c == '<' || c == '>')
        lexer->status = LEX_REDIRECT;
    else if (c == ' ' || c == '\t')
        lexer->status = LEX_NORMAL;
    else if (c == '\'')
        lexer->status = LEX_APOSTROPHE;
    else if (c == '\"')
        lexer->status = LEX_QUOTATION;
    else if (c == '|')
        lexer->status = LEX_PIPE;
    else if (c == '$')
        lexer->status = LEX_ENV;
    else if (lexer->status == LEX_NORMAL)
        lexer->status = LEX_STRING;
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
    return (cur == LEX_PIPE \
            ||(prev != LEX_NORMAL && cur == LEX_NORMAL) \
            || (prev != LEX_NORMAL && prev != cur));
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
    ft_lstclear(&(lexer->env_buffer), free);
    ft_lstclear(&(lexer->str_buffer), free);
    return (to_return);
}

void    put_token_to_list(int prev_status, t_lexer *lexer, t_list *token_list)
{
    t_token *token;
    
    token = get_token();
    token->status = prev_status;
    token->string = get_processed_string(lexer);
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

t_list	*tokenize(char *input, t_lexer *lexer)
{
	int     idx;
	int     prev_status;
    t_list *token_list;

	idx = 0;
    token_list = ft_lstnew(NULL);
	while (input[idx] != '\0') // '\0' == '\n'
	{
        prev_status = lexer->status;
		get_status(input[idx], lexer);
        add_char_to_buffer(char_ptr(&input[idx]), lexer);
        if (need_to_tokenize(prev_status, lexer->status))
            put_token_to_list(prev_status, lexer, token_list);
		idx++;
	}
    put_token_to_list(prev_status, lexer, token_list);
    return (token_list);
}

void    print_token(t_list *token_list)
{
    t_list *tmp;
    t_token *token;

    tmp = token_list->next; // token_list = HEAD
    while (tmp != NULL)
    {
        token = tmp->content;
        if (token->status == LEX_STRING)
            printf("{ status : STRING,");
        if (token->status == LEX_NORMAL)
            printf("{ status : NORMAL,");
        if (token->status == LEX_APOSTROPHE)
            printf("{ status : APOSTROPHE,");
        if (token->status == LEX_ENV)
            printf("{ status : ENV,");
        if (token->status == LEX_PIPE)
            printf("{ status : PIPE,");
        if (token->status == LEX_QUOTATION)
            printf("{ status : QUOTATION,");
        if (token->status == LEX_REDIRECT)
            printf("{ status : REDIRECT,");
        printf(" string: %s }\n", token->string);
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