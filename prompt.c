/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 21:42:34 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

// int main(int ac, char **av, char **envp)
// {
// 	char *input;

// 	(void)av;
// 	(void)envp;
// 	if (ac != 1)
// 		exit_error(ERR_ARGC);
// 	signal(SIGINT, sighandler);
// 	while (WAIT_FOR_SIG)
// 	{
// 		input = readline("$ AengMuShell> ");
// 		if (input == NULL) // EOF === Ctrl + D is not signal, catch and exit.
// 			return (1);
// 		if (get_len(input) == 0) // input nothing -> prompt
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		add_history(input);
// 		printf("Aengmu : %s\n", input);
// 	}
// }