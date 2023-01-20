/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/20 22:26:58 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_lexer *get_lexer(void)
{
	t_lexer *to_return;

	to_return = malloc(sizeof(t_lexer));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
    to_return->env_buffer = get_list();
    to_return->str_buffer = get_list();
	to_return->status = LEX_NORMAL;
    return (to_return);
}

void    get_status(char c, t_lexer *lexer)
{
    if (c == '<' || c == '>')
        lexer->status = LEX_REDIRECT;
    else if (c == ' ')
        lexer->status = LEX_NORMAL;
    else if (c == '\'')
        lexer->status = LEX_APOSTROPHE;
    else if (c == '\"')
        lexer->status = LEX_QUOTATION;
    else if (c == '|')
        lexer->status = LEX_PIPE;
    else if (c == '$')
        lexer->status = LEX_ENV;
    else
        lexer->status = LEX_STRING;
}

void    add_char_to_buffer(char *c, t_lexer *lexer)
{
    if (lexer->status == LEX_ENV)
        add_node(lexer->env_buffer, new_node(c));
    else
        add_node(lexer->str_buffer, new_node(c));
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
    t_node  *tmp;
    char    *string;

    string = malloc(sizeof(char) * (buffer->size + 1));
    string[buffer->size] = '\0';
    tmp = buffer->head;
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
    if (lexer->status != LEX_APOSTROPHE)
        env_string = buffer_to_string(lexer->env_buffer);
    string = buffer_to_string(lexer->str_buffer);
    to_return = ft_strjoin(string, env_string);
    if (env_string != NULL)
        free(env_string);
    free(string);
    return (to_return);
}

void    put_token_to_list(t_lexer *lexer, t_list *token_list)
{
    t_token *token;
    
    token = get_token();
    token->status = lexer->status;
    token->string = get_processed_string(lexer);
    add_node(token_list, new_node(token));
}

t_list	*tokenize(char *input, t_lexer *lexer)
{
	int     idx;
	int     prev_status;
    t_list *token_list;

	idx = 0;
    token_list = get_list();
	while (input[idx] != '\0') // '\0' == '\n'
	{
        prev_status = lexer->status;
		get_status(input[idx], lexer);
        add_char_to_buffer(&input[idx], lexer);
        if (need_to_tokenize(prev_status, lexer->status))
            put_token_to_list(lexer, token_list);
		idx++;
	}
    put_token_to_list(lexer, token_list);
    return (token_list);
}

void    print_token(t_token *token)
{
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
}

int main(int ac, char **av)
{
	t_lexer *lexer;
    t_list  *token_list;
	char    *input;
    t_node  *tmp;

	if (ac != 2)
		return (1);
	input = av[1];
	lexer = get_lexer();
	token_list = tokenize(input, lexer);

    tmp = token_list->head;
	while (tmp != NULL)
    {
        print_token((t_token *)tmp->content);
        tmp = tmp->next;
    }
	return (0);
}