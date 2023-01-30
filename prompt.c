/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 23:21:06 by sanan            ###   ########.fr       */
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
	char	*input;
	t_list	*processes;

	(void)av;
	(void)input;
	// atexit(check_leaks);
	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	while (WAIT_FOR_SIG)
	{
		input = readline("🐤AengMuShell $ ");
		if (input == NULL)
			return (1);
		if (get_len(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		processes = parse(envp, input);
		print_processes(processes);
		ft_lstclear(&processes, free);
		// system("leaks a.out");
		free(input);
	}
}