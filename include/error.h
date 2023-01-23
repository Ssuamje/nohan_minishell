/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:43:43 by sanan             #+#    #+#             */
/*   Updated: 2023/01/23 19:14:19 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
#include <stdio.h>
#include <stdlib.h>

// https://velog.io/@hidaehyunlee/minishell-4.-%EC%A2%85%EB%A3%8C%EC%83%81%ED%83%9C%EC%99%80-%EC%97%90%EB%9F%AC%EB%A9%94%EC%84%B8%EC%A7%80-%EC%B2%98%EB%A6%AC

enum e_exit_code{
    EXIT_GENERAL_SUCCESS,
    EXIT_GENERAL_ERROR,
    EXIT_BUILTIN_ERROR,
    EXIT_CANT_EXECUTE = 126,
    EXIT_COMMAND_NOT_FOUND,
    EXIT_SIGINT = 130, // 128 + SIGNO, CTRL + C == SIGINT == 2
    EXIT_SIGQUIT,

};

enum e_func_err{
    ERR_ARGC,
    ERR_MALLOC,
    ERR_STATUS,
};

void	exit_error(int error_code);

#endif