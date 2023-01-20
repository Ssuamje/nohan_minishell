/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:17:09 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 22:18:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../list/list.h"

typedef struct s_lexer{
	int     status;
	t_list  *env_buffer;
	t_list  *str_buffer;
}   t_lexer;

#endif