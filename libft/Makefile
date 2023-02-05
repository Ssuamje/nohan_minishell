# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 16:09:39 by sanan             #+#    #+#              #
#    Updated: 2023/02/05 23:20:07 by sanan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strrchr.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strdup.c\
ft_strldup.c\
ft_striteri.c\
ft_strlen.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strjoin.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_free_and_return.c\
ft_join_and_free.c\
ft_lstpop.c\
ft_putstr.c\
ft_strcmp.c


BONUS_SRC_FILES = ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c

OBJECTS = $(SRC_FILES:.c=.o)

BONUS_OBJECTS = $(BONUS_SRC_FILES:.c=.o)

CC = cc

WFLAG = -Wall -Wextra -Werror

ifdef BONUS
	ALL_OBJECTS = $(OBJECTS) $(BONUS_OBJECTS)
else
	ALL_OBJECTS = $(OBJECTS)
endif

all : $(NAME)

$(NAME) : $(ALL_OBJECTS)
	@ar rcus $@ $^

%.o: %.c
	@$(CC) -c $(WFLAG) $< -o $@

clean :
	@rm -rf $(OBJECTS) $(BONUS_OBJECTS)

fclean : clean
	@rm -rf $(NAME)

bonus :
	@make BONUS=1 all

re : fclean all

.PHONY : all clean fclean bonus re