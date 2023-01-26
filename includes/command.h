/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:49 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdio.h>
# include "redirection.h"
# include "libft.h"

void	command(t_proc *proc, t_fd *fd, char **path, char **envp);

#endif