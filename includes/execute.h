/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 13:39:01 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdio.h>
# include "redirection.h"
# include "libft.h"

void	execute(t_proc *proc, int pfd[], char **path, char **envp);

#endif