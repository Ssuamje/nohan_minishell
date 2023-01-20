# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungnoh <hyungnoh@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 11:37:37 by hyungnoh          #+#    #+#              #
#    Updated: 2022/11/22 19:30:14 by hyungnoh         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

OBJECT = ft_isalpha.o \
ft_isdigit.o \
ft_isalnum.o \
ft_isascii.o \
ft_isprint.o \
ft_strlen.o \
ft_memset.o \
ft_bzero.o \
ft_memcpy.o \
ft_memmove.o \
ft_strlcpy.o \
ft_strlcat.o \
ft_toupper.o \
ft_tolower.o \
ft_strchr.o \
ft_strrchr.o \
ft_strncmp.o \
ft_memchr.o \
ft_memcmp.o \
ft_strnstr.o \
ft_atoi.o \
ft_calloc.o \
ft_strdup.o \
ft_substr.o \
ft_strjoin.o \
ft_strtrim.o \
ft_split.o \
ft_itoa.o \
ft_strmapi.o \
ft_striteri.o \
ft_putchar_fd.o \
ft_putstr_fd.o \
ft_putendl_fd.o \
ft_putnbr_fd.o

OBJECT_B = ft_lstnew.o \
ft_lstadd_front.o \
ft_lstsize.o \
ft_lstlast.o \
ft_lstadd_back.o \
ft_lstdelone.o \
ft_lstclear.o \
ft_lstiter.o \
ft_lstmap.o

NAME = libft.a

HEADER = ./

COMPILE_YET = cc -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ_FILES = $(OBJECT) $(OBJECT_B)
else
	OBJ_FILES = $(OBJECT)
endif

all : $(NAME)
	
$(NAME) : $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

bonus :
	make WITH_BONUS=1

%.o : %.c
	$(COMPILE_YET) -I $(HEADER) -c $^ -o $@

clean :
	rm -f $(OBJECT) $(OBJECT_B)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re