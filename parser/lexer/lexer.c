/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/20 13:42:29 by sanan            ###   ########.fr       */
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
	
}

/**
 * 한 char씩 읽는다.
 * NORMAL이면 읽어야 하는 상태다.
 * 조합조건까지 계속 읽으면서 담는다.
 * 조합조건 *
 * 따옴표가 닫힐 때, 파이프를 만났을 때, 공백이 두 번 이상일 때 등등..
 * $가 나타난 경우, 본인의 상태에 따라서 환경변수를 해석할 지 말지를 결정한다.
 * 해석해야한다면, env_buffer에 담는다.
 * 
 * 
*/

// enum e_lexer_status{
// 	LEX_NORMAL,
// 	LEX_STRING,
// 	LEX_REDIRECT,
// 	LEX_QUOTATION,
// 	LEX_APOSTROPHE,
// 	LEX_PIPE,
// 	LEX_ENV,
// };


/**
 * lexer가 하는 일은 단순히 해석의 단위인 스트링 조각들을 묶어주는 것 뿐이다.
 * prev가 NORMAL일 때는 반드시 읽어야 한다.
 * ENV가 나오면, ENV인 동안에도 계속 읽어야 한다.
 * 
 * 
*/

void	lexical_analyze(char *input, t_lexer *lexer)
{
	int idx;
	int prev_status;

	idx = 0;
	prev_status = LEX_NORMAL;
	while (input[idx] != '\0')
	{
		
		idx++;
	}
}


// tokenizer에서 하는 작업.
int main(int ac, char **av)
{
	t_lexer *lexer;
	char *input;

	if (ac != 2)
		return (1);
	input = av[1];
	lexer = get_lexer();
	lexical_analyze(input, lexer);
	
	return (0);
}