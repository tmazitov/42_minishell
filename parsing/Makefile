# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:14:47 by emaravil          #+#    #+#              #
#    Updated: 2024/04/17 03:37:45 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# UNAME		=	$(shell uname)
NAME		=	parse.a
FLAGS		=	-Wall -Werror -Wextra
CC			= 	cc
RM			=	rm -rf
LB			= 	ar rcs

PARSE_SRCS	=	./src/parse/ft_parse.c \
				./src/parse/ft_tokenize.c \
				./src/parse/ft_writestring_p.c \
				./src/parse/print_split.c \
				./src/parse/ft_toktoast.c \
				./src/parse/ft_strtoken.c \
				./src/parse/ft_splittoken.c \
				./src/parse/ft_mergesplittoken.c \
				./src/parse/ft_parse_utils.c \
				./src/parse/ft_checknextchar.c \
				./src/grammar/ft_checksyntax.c \
				./src/grammar/ft_checkgrammar.c \
				./src/open_sh/ft_open_sh.c \
				./src/open_sh/ft_cleanopensh.c \
				./src/parse/ft_alloc.c \
				./src/parse/ft_split_utils.c
PARSE_OBJS	=	$(PARSE_SRCS:.c=.o)

HEADER		=	includes/parse.h

# LIBFT 		=	libft.a
# LIBFT_DIR 	=	../libft
# LIBFT_LIB 	=	$(LIBFT_DIR)/$(LIBFT)

MAKE_LIBR 	=	make --no-print-directory -C

%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

# all: $(PARSE_OBJS) $(LIBFT_LIB) $(NAME)
all: $(PARSE_OBJS) $(NAME)

# $(LIBFT_LIB):
# 	@$(MAKE_LIBR) $(LIBFT_DIR)

$(NAME): $(PARSE_OBJS)
	@$(LB) $(NAME) $(PARSE_OBJS)
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"

# ifeq ($(UNAME), Linux)
# $(NAME): $(PARSE_OBJS)
# 	@mkdir -p extracted_objs
# 	@ar x $(LIBFT_LIB) --output=extracted_objs
# 	@$(LB) $(NAME) $(PARSE_OBJS) extracted_objs/*.o
# 	@$(RM) extracted_objs
# 	@echo	"$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"
# else ifeq ($(UNAME), Darwin)
# $(NAME): $(LIBFT_LIB) $(PARSE_OBJS)
# 	@libtool -static -o $@ $^
# 	@echo	"$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"
# endif

clean:
	@$(RM) $(PARSE_OBJS)
	@echo "$(YELLOW) parse: OBJECT FILES DELETED!$(DEFAULT)"
# @$(MAKE_LIBR) $(LIBFT_DIR) clean

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED) parse: LIBRARY FILE DELETED!$(DEFAULT)"
# @$(RM) $(LIBFT_LIB)
# @echo "$(RED) libft: LIBRARY FILE DELETED!$(DEFAULT)"

re: fclean all

.PHONY: all bonus clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m