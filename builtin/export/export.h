/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:49:07 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 15:05:51 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../include/envl.h"
# include "../../include/utils.h"

int	builtin_export(char **cmd, t_list *envl);
int	is_cmd_has_special_after_builtin(char *cmd);

#endif