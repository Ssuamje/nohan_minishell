/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 23:16:32 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/error.h"
#include "readline/readline.h"
#include "./include/parser.h"
#include "./include/minishell.h"
#include "./include/envl.h"
#include "./include/utils.h"

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
	system("leaks minishell");
}

int	is_string_only_white_spaces(char *str)
{
	int idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (is_in_charset(str[idx], " \t") == FALSE)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

int	is_input_empty(char *input)
{
	return (get_len(input) == 0 \
		||	is_string_only_white_spaces(input));
}

int main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;
	t_list	*processes;

	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	g_envl = map_envp_to_list(envp);
	// atexit(check_leaks);
	// add_env_to_list(g_envl, "hello=world");
	// print_envl(g_envl);
	while (WAIT_FOR_SIG)
	{
		input = readline("🐤AengMuShell $ ");
		if (input == NULL)
			return (1);
		if (is_input_empty(input) == TRUE)
		{
			free(input);
			continue ;
		}
		add_history(input);
		processes = parse(g_envl, input);
		if (processes == NULL)
		{
			free(input);
			continue ;
		}
		print_processes_list(processes);
		exec_process(envp, processes);
		free_process_list(processes);
		free(input);
	}
}

//스페이스바 세그폴트