/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:24:45 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:26:36 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include <stdio.h>
# include <stdlib.h>

enum e_exit_code{
	EXIT_GENERAL_SUCCESS,
	EXIT_GENERAL_ERROR,
	EXIT_BUILTIN_ERROR,
	EXIT_CANT_EXECUTE = 126,
	EXIT_COMMAND_NOT_FOUND,
	EXIT_SIGINT = 130,
	EXIT_SIGQUIT,
};

enum e_func_err{
	ERR_ARGC,
	ERR_MALLOC,
	ERR_STATUS,
};

void	exit_error(int error_code);

#endif