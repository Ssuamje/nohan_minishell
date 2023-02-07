/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:38:47 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/07 20:08:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

void	interpret_redir_file(t_redir *redir)
{
	char	*tmp;

	if (ft_strncmp(redir->file, "~/", 2) == 0)
	{
		tmp = redir->file;
		redir->file = ft_join_and_free(\
				get_value_by_key(g_global->g_envl, "HOME"), \
				ft_join_and_free(ft_strdup("/"), ft_strdup(&(redir->file[2]))));
		free(tmp);
	}
}

void	redirection(t_process *proc)
{
	if (proc->redir_in != NULL)
		redirect_in(proc);
	if (proc->redir_out != NULL)
		redirect_out(proc);
}
