# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 12:22:10 by sanan             #+#    #+#              #
#    Updated: 2023/02/09 14:39:20 by sanan            ###   ########.fr        #
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
./envl/envl_utils_2.c \
./envl/envl_utils_3.c

SRC_ERROR = \
./error/error.c

SRC_EXECUTE = \
./execute/execute.c \
./execute/execute_utils_1.c \
./execute/execute_utils_2.c \
./execute/execute_utils_3.c \
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
./parser/parser_utils_7.c \
./parser/tokenizer/tokenizer.c \
./parser/tokenizer/tokenizer_utils_1.c \
./parser/tokenizer/tokenizer_utils_2.c \
./parser/tokenizer/tokenizer_utils_3.c \
./parser/tokenizer/tokenizer_utils_4.c \
./parser/tokenizer/tokenizer_utils_5.c \
./parser/tokenizer/tokenizer_utils_6.c \
./parser/lexer/lexer.c \
./parser/lexer/lexer_utils_1.c \
./parser/lexer/lexer_utils_2.c \
./parser/lexer/lexer_utils_3.c

SRC_REDIRECTION = \
./redirection/redirect_in.c \
./redirection/redirect_out.c \
./redirection/redirection.c \
./redirection/heredoc_utils_1.c \
./redirection/heredoc.c

SRC_UTILS = \
./utils/is_cmd_has_special_after.c \
./utils/is_in_str.c

SRC_PROMPT = \
./prompt/prompt.c \
./prompt/prompt_utils_1.c \
./prompt/prompt_utils_2.c \
./prompt/prompt_utils_3.c

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
	@$(ECHO) $(PURPLE) "🐤 AengMu : I'm Ready!" $(RESET)

$(NAME) : $(OBJS) $(LIB_FT)
	@$(ECHO) $(CYAN) 🐤 assembling $(GREEN) $@
	@$(CC) $(WFLAGS) $(SRCS) $(LIB_FT) $(READLINE_CMP_LINK) $(INCLUDE) -o $(NAME)

%.o : %.c
	@$(ECHO) $(BLUE) 🐤 compiling $(GREEN) $<
	@$(CC) $(WFLAGS) $(INCLUDE) -c $< -o $@

$(LIB_FT) :
	@$(ECHO) $(BLUE) 🐤 compiling $(GREEN) $@
	@make -C $(dir $(LIB_FT)) bonus

clean :
	@make -C $(dir $(LIB_FT)) clean
	@rm -rf $(OBJS)
	@echo $(RED) "	   🐤 cleaned object files!" $(RESET)

fclean : clean
	@make -C $(dir $(LIB_FT)) fclean
	@rm -rf $(NAME)
	@echo $(RED) "	   🐤 cleaned archive, target files!" $(RESET)

re :
	@make fclean
	@make all

RESET	=	"\x1b[0m"
GREY	=	"\x1b[30m"
RED		=	"\x1b[31m"
GREEN	=	"\x1b[32m"
YELLOW	=	"\x1b[33m"
BLUE	=	"\x1b[34m"
PURPLE	=	"\x1b[35m"
CYAN	=	"\x1b[36m"
WHITE	=	"\x1b[37m"

ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo $(YELLOW) "`expr " [ \`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`% ]" $(RESET)
endif

.PHONY : all clean fclean re