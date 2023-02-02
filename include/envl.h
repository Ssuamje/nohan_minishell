/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:54:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:24:27 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVL_H
# define ENVL_H

# include "libft.h"
# include "error.h"

typedef struct s_environ{
	char	*key;
	char	*value;
}	t_environ;

t_list	*map_envp_to_list(char **envp);
void	add_env_to_list(t_list *envl, char *env);

#endif