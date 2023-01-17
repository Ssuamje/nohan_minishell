/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:34:05 by sanan             #+#    #+#             */
/*   Updated: 2023/01/17 19:56:26 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_gc	*get_garbage_collector(void)
{
	t_gc *to_return;

	to_return = malloc(sizeof(t_gc));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->head = NULL;
	to_return->tail = NULL;
	to_return->size = 0;
	return (to_return);
}

void	init_garbage_collector(t_gc *collector)
{
	collector->head = NULL;
	collector->tail = NULL;
	collector->size = 0;
}

t_gbg	*new_garbage(void **garbage_ptr, int type)
{
	t_gbg *garbage;

	garbage = malloc(sizeof(t_gbg));
	if (garbage == NULL)
		exit_error(ERR_MALLOC);
	garbage->garbage_ptr = garbage_ptr;
	garbage->type = type;
	garbage->next = NULL;
	return (garbage);
}

void    add_garbage(t_gc *collector, void **garbage_ptr, int type)
{
	t_gbg *garbage;

	garbage = new_garbage(garbage_ptr, type);
	if (collector->size == 0)
	{
		collector->head = garbage;
		collector->tail = garbage;
	}
	else
	{
		collector->tail->next = garbage;
		collector->tail = garbage;
	}
	(collector->size)++;
}

void free_string(void **garbage_ptr)
{
	(void)garbage_ptr;
	write(1, "i got string!\n", 14);
}

void free_lexer(void **garbage_ptr)
{
	(void)garbage_ptr;
	write(1, "i got lexer!\n", 13);
}

void free_node_list(void **garbage_ptr)
{
	(void)garbage_ptr;
	write(1, "i got node list!\n", 17);
}

void free_token_list(void **garbage_ptr)
{
	(void)garbage_ptr;
	write(1, "i got token list!\n", 18);
}

void	sweep_garbage(t_gbg *garbage) // 알맹이만 제거
{
	if (garbage->type == GBG_STRING)
		free_string(garbage->garbage_ptr);
	if (garbage->type == GBG_LEXER)
		free_lexer(garbage->garbage_ptr);
	if (garbage->type == GBG_NODE_LIST)
		free_node_list(garbage->garbage_ptr);
	if (garbage->type == GBG_TOKEN_LIST)
		free_token_list(garbage->garbage_ptr);
}

void	realease_collector(t_gc **collector) // garbage 껍데기만 남았을 때
{
	t_gbg *tmp;
	t_gbg **tmp_ptr;

	tmp = (*collector)->head;
	tmp_ptr = &((*collector)->head);
	while (tmp->next != NULL) // garbage 리스트의 끝까지
	{
		free(tmp);
		tmp = (*tmp_ptr)->next;
		(*tmp_ptr) = NULL;
		tmp_ptr = &(tmp);
	}
	free(*collector);
	collector = NULL;
}

void	sweep_all_garbages(t_gc **collector) // 순회하면서 collector까지 해제
{
	t_gbg *tmp;

	tmp = (*collector)->head;
	while (tmp != NULL)
	{
		sweep_garbage(tmp);
		tmp = tmp->next;
	}
	realease_collector(collector);
}