/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:01:22 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 12:01:23 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

#define REDIR_IN 0
#define REDIR_OUT 1

void	print_redir(t_redir *redir)
{
	if (redir->flag == IN_TRUNC)
		printf("	{ type : <\n");
	if (redir->flag == IN_APPEND)
		printf("	{ type : <<\n");
	if (redir->flag == OUT_TRUNC)
		printf("	{ type : >\n");
	if (redir->flag == OUT_APPEND)
		printf("	{ type : >>\n");
	printf("  	file = _%s_}\n", redir->file);
	printf("\n");
}

void	print_redir_list(t_list *redir_list)
{
	t_list	*tmp;
	t_redir	*cur;

	tmp = redir_list->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		print_redir(cur);
		tmp = tmp->next;
	}
}
