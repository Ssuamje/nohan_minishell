/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/19 22:20:26 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error/error.h"
# include "parser/parser.h"

void    check_leask(void) // need to delete
{
    system("leaks a.out");
}

enum e_lexer_status{
	LEX_NORMAL, // 입력을 받기 위해 대기중인 상태
	LEX_STRING, // sadfjksadfjkl
	LEX_REDIRECT, // <, >, <<, >>
	LEX_QUOTATION, // ""
	LEX_APOSTROPHE, // ''
	LEX_PIPE, // |
	LEX_ENV, // $
};

#endif