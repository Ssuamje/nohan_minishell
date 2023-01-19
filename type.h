/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:06:23 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 21:23:41 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H
# include <fcntl.h> // flag of redir

typedef struct s_node{
	void            *content;
	struct s_node   *next;
}   t_node;

typedef struct s_list{
	t_node *head;
	t_node *tail;
	int     size;
}   t_list;

enum e_flag_redir{
	IN_TRUNC, // <
	IN_ADD, // <<
	OUT_TRUNC, // >
	OUT_ADD, // >>
};

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