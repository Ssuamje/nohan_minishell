/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:41:05 by sanan             #+#    #+#             */
/*   Updated: 2023/01/17 19:55:36 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H
# include <stdlib.h>
# include "../tokenizer/minishell.h" // exit_error

typedef struct s_gbg{
	int type;
	void **garbage_ptr; // 포인터의 포인터로 NULL까지
	struct s_gbg *next;
}   t_gbg;

typedef struct s_gc{
	t_gbg	*head;
	t_gbg	*tail;
	int    	size;
}   t_gc;

enum e_garbage_type{
	GBG_STRING,
	GBG_LEXER,
	GBG_NODE_LIST,
	GBG_TOKEN_LIST,
};

t_gc    *get_garbage_collector(void);
void	init_garbage_collector(t_gc *collector);
t_gbg	*new_garbage(void **garbage_ptr, int type);
void    add_garbage(t_gc *collector, void **garbage_ptr, int type);
void	sweep_garbage(t_gbg *garbage);
void	sweep_all_garbages(t_gc **collector);
void	realease_collector(t_gc **collector);


#endif