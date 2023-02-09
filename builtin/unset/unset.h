/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:16:39 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 15:05:43 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

# include "../../include/envl.h"
# include "../export/export.h"
# include "../../include/utils.h"

int	builtin_unset(char **cmd, t_list *envl);

#endif