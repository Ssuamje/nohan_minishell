/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 23:05:18 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdio.h>
# include "redirection.h"
# include "libft.h"
# include "parser.h"

void	execute(t_process *cur, t_process *next, char **path, char **envp);

#endif