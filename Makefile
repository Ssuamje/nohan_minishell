# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 12:22:10 by sanan             #+#    #+#              #
#    Updated: 2023/02/05 19:52:10 by hyungnoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_BUILTIN = \
 ./builtin/cd/cd.c \
 ./builtin/echo/echo.c \
 ./builtin/exit/exit.c \
 ./builtin/export/export.c \
 ./builtin/pwd/pwd.c \
 ./builtin/unset/unset.c \
 ./builtin/env/env.c

SRC_ENVL = \
./envl/envl.c \
./envl/envl_utils_1.c \
./envl/envl_utils_2.c

SRC_ERROR = \
./error/error.c

SRC_EXECUTE = \
./execute/execute.c \
./execute/exec_process.c \
./execute/env_path.c

SRC_PARSER = \
./parser/parser.c \
./parser/parser_utils_1.c \
./parser/parser_utils_2.c \
./parser/parser_utils_3.c \
./parser/parser_utils_4.c \
./parser/parser_utils_5.c \
./parser/parser_utils_6.c \
./parser/tokenizer/tokenizer.c \
./parser/tokenizer/tokenizer_utils_1.c \
./parser/tokenizer/tokenizer_utils_2.c \
./parser/tokenizer/tokenizer_utils_3.c \
./parser/tokenizer/tokenizer_utils_4.c \
./parser/tokenizer/tokenizer_utils_5.c \
./parser/lexer/lexer.c \
./parser/lexer/lexer_utils_1.c \
./parser/lexer/lexer_utils_2.c \
./parser/lexer/lexer_utils_3.c

SRC_REDIRECTION = \
./redirection/redirect_in.c \
./redirection/redirect_out.c \
./redirection/redirection.c \
./redirection/heredoc.c

SRC_UTILS = \
./utils/is_cmd_has_special_after.c \
./utils/is_in_str.c \
./utils/print_process.c \
./utils/print_redir.c \
./utils/print_split.c \
./utils/print_token.c

SRC_PROMPT = \
./prompt/prompt.c \
./prompt/prompt_utils_1.c

SRCS = \
$(SRC_BUILTIN) \
$(SRC_ENVL) \
$(SRC_ERROR) \
$(SRC_EXECUTE) \
$(SRC_PARSER) \
$(SRC_REDIRECTION) \
$(SRC_UTILS) \
$(SRC_PROMPT)

OBJS = $(SRCS:.c=.o)

CC = cc

WFLAGS = -Wall -Wextra -Werror

READLINE_CMP_LINK = -L$(shell brew --prefix readline)/lib/ -lreadline
READLINE_INCLUDE = -I$(shell brew --prefix readline)/include/

LIB_FT = ./libft/libft.a

INCLUDE = -I./include $(READLINE_INCLUDE)

all : $(NAME)

$(NAME) : $(OBJS) $(LIB_FT)
	$(CC) $(WFLAGS) $(SRCS) $(LIB_FT) $(READLINE_CMP_LINK) $(INCLUDE) -o $(NAME)

%.o : %.c
	$(CC) $(WFLAGS) $(INCLUDE) -c $< -o $@

$(LIB_FT) :
	make -C $(dir $(LIB_FT)) bonus

clean :
	make -C $(dir $(LIB_FT)) clean
	rm -rf $(OBJS)

fclean : clean
	make -C $(dir $(LIB_FT)) fclean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re