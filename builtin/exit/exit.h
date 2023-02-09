/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:45:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 13:59:42 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "../../include/envl.h"

void	builtin_exit(char **cmd, t_list *envl);
int		convert_question_value_and_free(char *value);

#endif