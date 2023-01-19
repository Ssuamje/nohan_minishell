/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:24 by sanan             #+#    #+#             */
/*   Updated: 2023/01/19 21:44:28 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	exit_error(int error_code)
{
	char *msg;

	msg = NULL;
	if (error_code == ERR_ARGC)
		msg = "Error : Argument counts is not correct.\n";
	if (error_code == ERR_MALLOC)
		msg = "Error : Memory allocation has failed.\n";
	printf("%s", msg);
	exit(EXIT_FAILURE);
}