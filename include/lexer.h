/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:17:09 by sanan             #+#    #+#             */
/*   Updated: 2023/01/20 22:28:11 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "list.h"
#include "error.h"
#include "tokenizer.h"
// #include "../libft/libft.h"

enum e_lexer_status{
	LEX_NORMAL, // 입력을 받기 위해 대기중인 상태
	LEX_STRING, // sadfjksadfjkl
	LEX_REDIRECT, // <, >, <<, >>
	LEX_QUOTATION, // ""
	LEX_APOSTROPHE, // ''
	LEX_PIPE, // |
	LEX_ENV, // $
};
typedef struct s_lexer{
	int     status;
	t_list  *env_buffer;
	t_list  *str_buffer;
}   t_lexer;

#endif