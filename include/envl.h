/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:54:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 19:56:45 by sanan            ###   ########.fr       */
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

typedef struct s_global{
	t_list	*g_envl;
	int		g_sigint_flag;
}	t_global;

t_global	*g_global;

t_list		*map_envp_to_list(char **envp);
void		add_set_env_to_list(t_list *envl, char *env);
void		print_envl(t_list *envl);
int			is_key_in_envl(t_list *envl, char *key);
t_environ	*find_env_by_key(t_list *envl, char *key);
void		add_only_key_to_list(t_list *envl, char *env);
void		delete_env_by_key(t_list *envl, char *key);
char		**envl_to_envp(t_list *envl);
t_environ	*find_env_by_key(t_list *envl, char *key);
char		*get_value_by_key(t_list *envl, char *key);
void		set_exit_code(t_list *envl, int exit_code);
t_environ	*get_environ(void);
void		sort_envl(t_list *envl);

#endif