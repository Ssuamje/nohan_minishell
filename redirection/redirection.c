/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:38:47 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/03 00:41:42 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

void	redirection(t_process *proc)
{
	if (proc->redir_in != NULL)
		redirect_in(proc);
	if (proc->redir_out != NULL)
		redirect_out(proc);
}
