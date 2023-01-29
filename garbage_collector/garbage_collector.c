/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:34:05 by sanan             #+#    #+#             */
/*   Updated: 2023/01/29 21:38:32 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	clear_list(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		*list = tmp->next;
		free(tmp);
		tmp = *list;
	}
}

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

t_gbg	*new_garbage(void *garbage_ptr, int type)
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

void    add_garbage(t_gc *collector, void *garbage_ptr, int type)
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

void free_string(void *garbage_ptr)
{
	if (garbage_ptr)
		free(garbage_ptr);
	garbage_ptr = NULL;
}

void free_node_list(void *garbage_ptr) // head 살리고 선회 free
{
	t_list *gbg_ptr;

	gbg_ptr = garbage_ptr;
	clear_list(&gbg_ptr);
	free(gbg_ptr);
}

void free_lexer(void *garbage_ptr)
{
	t_lexer *gbg_ptr;

	gbg_ptr = garbage_ptr;
	if (gbg_ptr->env_buffer)
	{
		clear_list(&(gbg_ptr->env_buffer)); // free_node_list
		gbg_ptr->env_buffer = NULL;
	}
	if (gbg_ptr->str_buffer)
	{
		clear_list(&(gbg_ptr->str_buffer));
		gbg_ptr->str_buffer = NULL;
	}
}


void free_tokens(void **garbage_ptr)
{
	(void)garbage_ptr;
	write(1, "i got token list!\n", 18);
}

void	sweep_garbage(t_gbg *garbage) // 알맹이만 제거
{
	if (garbage->type == GBG_STRING && garbage->garbage_ptr != NULL)
		free_string(garbage->garbage_ptr);
	if (garbage->type == GBG_LEXER && garbage->garbage_ptr != NULL)
		free_lexer(garbage->garbage_ptr);
	if (garbage->type == GBG_NODE_LIST && garbage->garbage_ptr != NULL)
		free_node_list(garbage->garbage_ptr);
	if (garbage->type == GBG_tokens && garbage->garbage_ptr != NULL)
		free_tokens(garbage->garbage_ptr);
}

void	clear_collector(t_gc *collector) // garbage 껍데기만 남았을 때
{
	t_gbg *tmp;
	t_gbg **tmp_ptr;

	tmp = collector->head;
	tmp_ptr = &(collector->head);
	while (tmp->next != NULL) // garbage 리스트의 끝까지
	{
		free(tmp);
		tmp = (*tmp_ptr)->next;
		tmp_ptr = &(tmp);
	}
	if (tmp)
		free(tmp);
	free(collector);
}

void	sweep_all_garbages(t_gc *collector) // 순회하면서 collector까지 해제
{
	t_gbg *tmp;

	tmp = collector->head;
	while (tmp != NULL)
	{
		sweep_garbage(tmp);
		tmp = tmp->next;
	}
	clear_collector(collector);
}