/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/01/26 21:49:34 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/error.h"
#include "readline/readline.h"
#include "./include/parser.h"
#define WAIT_FOR_SIG 1


int get_len(char *str)
{
	int idx;
	
	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

void    sighandler(int signo)
{
	if (signo == SIGINT)
		printf("AengMu : You can quit by only Ctrl + D\n");
}

//need to delete
#include <unistd.h>
void check_leaks(void)
{
	char *str = "\n**********************PROGRAM END************************\n";
	write(1, str, ft_strlen(str));
	system("leaks a.out");
}

int main(int ac, char **av, char **envp)
{
	char *input;
	t_lexer *lexer;
	t_list *token_list;

	(void)av;
	atexit(check_leaks);
	lexer = NULL;
	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	print_envp(envp);
	while (WAIT_FOR_SIG)
	{
		input = readline("$ AengMuShell> ");
		if (input == NULL) // EOF === Ctrl + D is not signal, catch and exit.
			return (1);
		if (get_len(input) == 0) // input nothing -> prompt
		{
			free(input);
			continue ;
		}
		add_history(input);
		lexer = get_lexer();
		token_list = tokenize(input, lexer);
		process_token_list_env(envp, token_list);
		print_token(token_list);
		system("leaks a.out");
		free_token_list(&token_list);
		free(lexer);
		free(input);
	}
}