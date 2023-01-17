/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/17 19:43:02 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../garbage_collector/garbage_collector.h"

typedef struct s_list{
	char			character;
	struct s_list	*next;
}   t_list;

typedef struct s_lexer{
	int status;
	t_list *env_buffer;
	t_list *str_buffer;
}   t_lexer;

typedef struct s_token{
	int				status; // 최종 상태는 STRING, REDIRECT, PIPE 셋 중에 하나다.
	char 			*string;
	struct s_token	*next;
}   t_token;

enum e_lexer_status{
	NORMAL, // 입력을 받기 위해 대기중인 상태
	STRING, // sadfjksadfjkl
	REDIRECT, // <, >, <<, >>
	QUOTATION, // ""
	APOSTROPHE, // ''
	PIPE, // |
	ENV, // $
};

enum e_error{
	ERR_ARGC,
	ERR_MALLOC,
};

void	exit_error(int error_code);

#endif