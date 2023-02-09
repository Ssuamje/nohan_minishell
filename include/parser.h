/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:20:29 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:36:55 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "redirection.h"
# include "tokenizer.h"
# include "utils.h"

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

typedef struct s_parser{
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
	int		pfd[2];
	char	**cmd;
}	t_process;

t_list		*parse(t_list *envl, char *input);
void		*free_process_return_null(t_list **tokens, t_list *processes, \
								t_parser *parser);
void		*free_token_return_null(t_list **tokens, char *msg);
int			syntax_string(t_token *cur);
int			syntax_redirect(t_token *cur);
int			syntax_quotes(t_token *cur);
int			syntax_pipe(t_token *cur);
int			syntax_env(t_token *cur);
int			is_token_not_env_not_has_special(t_token *token);
int			check_first_arg(t_token *token);
int			get_redir_flag(char *redir);
void		free_parser(t_parser **parser);
t_process	*get_process(void);
t_parser	*get_parser(void);
int			check_join_condition(t_token *next_token);
void		join_tokens(t_list *tokens);
int			parse_init(t_token *token, t_parser *parser);
t_redir		*get_redir(t_parser *parser);
int			parse_string(t_token *token, t_parser *parser);
void		put_redir_token(t_parser *parser, t_process *cur_proc);
int			parse_redirect(t_token *token, t_parser *parser, \
							t_process *cur_proc);
void		argv_list_to_split(t_process *cur_proc, t_parser *parser);
void		check_syntax_by_type(t_token *token, int *err);
int			check_syntax(t_list *tokens);
int			check_args_first(t_list *tokens);
void		free_process(t_process *process);
void		free_process_list(t_list *processes);
void		seperate_process_by_pipe(t_process **proc, t_parser *parser, \
								t_list *processes);
int			is_parser_string_status(t_parser *parser);
void		parse_by_type(t_token *token, t_parser *parser, \
					t_process *proc, int *err);
int			parse_tokens(t_list *tokens, t_list *processes, t_parser *parser);
void		free_redir_list(t_list	**redir);
int			parse_init(t_token *token, t_parser *parser);

#endif