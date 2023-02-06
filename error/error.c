/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:24 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 11:54:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

void	exit_error(int error_code)
{
	char	*msg;

	msg = NULL;
	if (error_code == ERR_ARGC)
		msg = "Usage : ./minishell *NO ARGS*\n";
	if (error_code == ERR_MALLOC)
		msg = "Error : Memory allocation has failed.\n";
	if (error_code == ERR_STATUS)
		msg = "Error : Failed parsing due to unexpected lexer status.\n";
	printf("%s", msg);
	exit(EXIT_FAILURE);
}
