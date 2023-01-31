/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:20:29 by sanan             #+#    #+#             */
/*   Updated: 2023/01/31 20:42:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "redirection.h"
# include "tokenizer.h"

enum e_parser_status{
	PAR_STRING = 1,
	PAR_REDIRECT,
	PAR_QUOTATION,
	PAR_APOSTROPHE,
	PAR_PIPE,
	PAR_ENV,
};

enum	e_err_join{
	ERR_TRUE,
	ERR_FALSE
};

typedef	struct s_parser{
	int		status;
	int		flag_redir;
	char	*string;
	t_list	*argv;
}	t_parser;

typedef struct s_process{
	t_list	*redir_in;
	t_list	*redir_out;
	int		fd_infile;
	int		fd_outfile;
	char	**cmd;
}	t_process;


t_list *parse(char **envp, char *input);
void	free_parser(t_parser **parser);
int	check_syntax(t_list *tokens);
t_process	*get_process(void);
t_parser	*get_parser(void);
int	parse_init(t_token *token, t_parser *parser);
void	print_processes(t_list *processes);

#endif