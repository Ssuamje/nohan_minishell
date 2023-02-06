/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:38:47 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/06 18:09:18 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

void	redirection(t_process *proc, t_info *info)
{
	if (proc->redir_in != NULL && info->err_flag == 0)
		redirect_in(proc, info);
	if (proc->redir_out != NULL && info->err_flag == 0)
		redirect_out(proc, info);
}
