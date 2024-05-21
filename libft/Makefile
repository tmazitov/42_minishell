# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:14:47 by emaravil          #+#    #+#              #
#    Updated: 2024/05/19 22:55:36 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
FLAGS		=	-Wall -Werror -Wextra
CC			= 	cc
RM			=	rm -rf
LB			= 	ar rcs

COMP_SRCS	=	ft_compare/ft_isalnum.c \
				ft_compare/ft_isalpha.c \
				ft_compare/ft_isascii.c \
				ft_compare/ft_isdigit.c \
				ft_compare/ft_isprint.c \
				ft_compare/ft_isspace.c
COMP_OBJS	=	$(COMP_SRCS:.c=.o)

CONV_SRCS	=	ft_convert/ft_atoi.c \
				ft_convert/ft_itoa.c \
				ft_convert/ft_tolower.c \
				ft_convert/ft_toupper.c
CONV_OBJS	=	$(CONV_SRCS:.c=.o)

GNL_SRCS	=	ft_gnl/get_next_line.c \
				ft_gnl/get_next_line_utils.c \
				ft_gnl/get_next_line_utilsb.c \
				# ft_gnl/get_next_line_bonus.c \
				# ft_gnl/get_next_line_utils_bonus.c
GNL_OBJS	=	$(GNL_SRCS:.c=.o)

HNDL_SRCS	=	ft_handles/ft_handle_errors.c
HNDL_OBJS	=	$(HNDL_SRCS:.c=.o)

LIST_SRCS	=	ft_list/ft_lstadd_back.c \
				ft_list/ft_lstadd_front.c \
				ft_list/ft_lstclear.c \
				ft_list/ft_lstdelone.c \
				ft_list/ft_lstiter.c \
				ft_list/ft_lstlast.c \
				ft_list/ft_lstmap.c \
				ft_list/ft_lstnew.c \
				ft_list/ft_lstsize.c
LIST_OBJS	=	$(LIST_SRCS:.c=.o)

MEM_SRCS	=	ft_memory/ft_bzero.c \
				ft_memory/ft_calloc.c \
				ft_memory/ft_memchr.c \
				ft_memory/ft_memcmp.c \
				ft_memory/ft_memcpy.c \
				ft_memory/ft_memmove.c \
				ft_memory/ft_memset.c \
				ft_memory/ft_realloc.c
MEM_OBJS	=	$(MEM_SRCS:.c=.o)

PRNTF_SRCS	=	ft_printf/ft_checkerror.c \
				ft_printf/ft_checkerror_malloc.c \
				ft_printf/ft_get_args.c	\
				ft_printf/ft_getprintlength.c \
				ft_printf/ft_print_c.c \
				ft_printf/ft_print_checkspace.c \
				ft_printf/ft_print_numbase.c \
				ft_printf/ft_print_p.c \
				ft_printf/ft_print_prefix.c \
				ft_printf/ft_print_s.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printpercent.c
PRNTF_OBJS	=	$(PRNTF_SRCS:.c=.o)

STR_SRCS	=	ft_strings/ft_split.c \
				ft_strings/ft_strchr.c \
				ft_strings/ft_strdup.c \
				ft_strings/ft_striteri.c \
				ft_strings/ft_strjoin.c \
				ft_strings/ft_strlcat.c \
				ft_strings/ft_strlcpy.c \
				ft_strings/ft_strlen.c \
				ft_strings/ft_strmapi.c \
				ft_strings/ft_strncmp.c \
				ft_strings/ft_strnstr.c \
				ft_strings/ft_strstr.c \
				ft_strings/ft_strrchr.c \
				ft_strings/ft_strtrim.c \
				ft_strings/ft_substr.c
STR_OBJS	=	$(STR_SRCS:.c=.o)

WRT_SRCS	=	ft_write/ft_putchar_fd.c \
				ft_write/ft_putendl_fd.c \
				ft_write/ft_putnbr_fd.c \
				ft_write/ft_putstr_fd.c
WRT_OBJS	=	$(WRT_SRCS:.c=.o)

HEADER		=	libft/ft_printf.h \
				libft/get_next_line.h \
				libft/libft.h

%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(COMP_OBJS) $(CONV_OBJS) $(GNL_OBJS) $(HNDL_OBJS) $(LIST_OBJS) $(MEM_OBJS) $(PRNTF_OBJS) $(STR_OBJS) $(WRT_OBJS)
	@$(LB) $(NAME) $(COMP_OBJS) $(CONV_OBJS) $(GNL_OBJS) $(HNDL_OBJS) $(LIST_OBJS) $(MEM_OBJS) $(PRNTF_OBJS) $(STR_OBJS) $(WRT_OBJS)
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"

clean:
	@$(RM) $(COMP_OBJS)
	@$(RM) $(CONV_OBJS)
	@$(RM) $(GNL_OBJS)
	@$(RM) $(HNDL_OBJS)
	@$(RM) $(LIST_OBJS)
	@$(RM) $(MEM_OBJS)
	@$(RM) $(PRNTF_OBJS)
	@$(RM) $(STR_OBJS)
	@$(RM) $(WRT_OBJS)
# @echo "$(YELLOW) libft: OBJECT FILES DELETED!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
# @echo "$(RED) libft: LIBRARY AND OBJECTS DELETED!$(DEFAULT)"

re:	fclean all

.PHONY: all bonus clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m