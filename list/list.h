/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:05:56 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 22:15:08 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_node{
	void            *content;
	struct s_node   *next;
}   t_node;

typedef struct s_list{
	t_node *head;
	t_node *tail;
	int     size;
}   t_list;

t_list  *get_list(void);
t_node  *new_node(void *content);
void    add_node(t_list *list, t_node *node);
void    delete_node(t_node **node);

#endif