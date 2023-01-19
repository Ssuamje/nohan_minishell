/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:06:23 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 22:19:12 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H
# include "list/list.h"
# include <fcntl.h> // flag of redir

enum e_flag_redir{
	IN_TRUNC, // <
	IN_ADD, // <<
	OUT_TRUNC, // >
	OUT_ADD, // >>
}; // 덧붙이는건 마땅한 이름이 기억이 안나서 그냥 이렇게 했음. 원하면 수정 가능

typedef struct s_redir{
	int flag;
	char *directory;
}   t_redir;

typedef struct s_proc{
	t_list  *redir_in; // {flag : IN_TRUNC, directory: "INFILE"}
	t_list  *redir_out;// {flag : OUT_ADD, directory: "OUTFILE"}
	char    **command; // {"git", "branch", "-D", "this_branch_is_for_example"}
}   t_proc;

#endif