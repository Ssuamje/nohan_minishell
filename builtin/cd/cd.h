/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:26:45 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 23:06:37 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../../include/execute.h"

int		builtin_cd(t_process *cur);
void	interpret_home_set_dir_flag(t_process *cur, char **dir, int *flag);

#endif