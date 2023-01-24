/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:56:58 by sanan             #+#    #+#             */
/*   Updated: 2023/01/24 15:08:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

t_list	*tokenize(char *input, t_lexer *lexer)
{                                   
	int     idx;
    t_list *token_list;

	idx = 0;
    token_list = ft_lstnew(NULL);
	while (input[idx] != '\0')
	{
        lexical_analyze(token_list, &input[idx], lexer);
		idx++;
	}
    if (lexer->status != LEX_NORMAL)
        put_token_to_list(lexer, token_list);
    return (token_list);
}

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

void    put_token_to_list(t_lexer *lexer, t_list *token_list)
{
    t_token *token;
    char    *tmp;
    
    token = get_token();
    token->status = lexer->status;
    token->string = get_processed_string(lexer);
    tmp = token->string;
    token->string = ft_strtrim(tmp, " \t");
    free(tmp);
    ft_lstadd_back(&token_list, ft_lstnew(token));
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
//delete
void check_leaks(void)
{
    system("leaks a.out");
}

void free_token_list(t_list **token_list)
{
    t_list *tmp;

    tmp = *token_list;
    while (tmp)
    {
        *token_list = tmp->next;
        if (tmp->content)
            free(((t_token *)tmp->content)->string);
        ft_lstdelone(tmp, free);
        tmp = *token_list;
    }
}

int main(int ac, char **av)
{
	t_lexer *lexer;
    t_list  *token_list;

    atexit(check_leaks);
	if (ac != 2)
		return (1);
	lexer = get_lexer();
	token_list = tokenize(av[1], lexer);
    print_token(token_list);
    //parser = get_parser();
    //processes = get_process_list();
    //parse_token_list(token_list, parser, processes);
    free_token_list(&token_list);
    free(lexer);
    //return (processes);
	return (0);
}

// apostrophe는 그 안의 모든 것을 문자열로 받아버린다.
// quotation은 그 안의 모든 것을 문자열로 받지만, 변수는 해석한다.