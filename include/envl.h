/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:54:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:58:49 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVL_H
# define ENVL_H

# include "libft.h"
# include "bool.h"
# include "error.h"

typedef struct s_environ{
	char	*key;
	char	*value;
}	t_environ;

t_list		*map_envp_to_list(char **envp);
void		add_env_to_list(t_list *envl, char *env);
void		print_envl(t_list *envl);
int			is_key_in_envl(t_list *envl, char *key);
t_environ	*find_env_by_key(t_list *envl, char *key);

#endif