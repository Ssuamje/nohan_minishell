/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:06:20 by sanan             #+#    #+#             */
/*   Updated: 2023/01/21 18:51:02 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/list.h"
#include "../include/error.h"

t_list  *get_list(void)
{
    t_list *to_return;

    to_return = malloc(sizeof(t_list));
    if (to_return == NULL)
        exit_error(ERR_MALLOC);
    to_return->head = NULL;
    to_return->tail = NULL;
    to_return->size = 0;
    return (to_return);
}

void    set_list(t_list *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

t_node  *new_node(void *content)
{
    t_node  *to_return;

    to_return = malloc(sizeof(t_node));
    if (to_return == NULL)
        exit_error(ERR_MALLOC);
    to_return->content = content;
    to_return->next = NULL;
    return (to_return);
}

void    add_node(t_list *list, t_node *node)
{
    if (list->size == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    (list->size)++;
}

void    delete_node(t_node **node) // content는 타입에 맞게 따로 free
{
    free(*node);
    *node = NULL;
}

void    clean_list(t_list *list)
{
    t_node *tmp;
    t_node *next;

    tmp = list->head;
    if (tmp == NULL)
        return ;
    while (tmp->next != NULL)
    {
        next = tmp->next;
        if (tmp->content)
            free(tmp->content);
        delete_node(&tmp);
        tmp = next;
    }
    if (tmp)
    {
        free(tmp->content);
        delete_node(&tmp);
    }
}