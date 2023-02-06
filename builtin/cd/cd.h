/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:26:45 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 19:04:06 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../../include/execute.h"

int	builtin_cd(t_process *cur);
void	interpret_home_set_dir_flag(t_process *cur, char **dir, int *flag);

#endif