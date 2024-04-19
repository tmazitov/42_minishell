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

# THIS MAKEFILE IS FOR TESTING

NAME			= 	builtins
CC				= 	cc
FLAGS			= 	-Wall -Wextra -Werror -fsanitize=address
RM				= 	rm -rf
LB				= 	ar rcs

BUILTINS_SRCS	=	./echo/ft_echo.c \
					main.c\
					./utils/builtin_utils.c
BUILTINS_OBJS	=	$(BUILTINS_SRCS:.c=.o)
HEADER		=	./builtins.h

PARSE = parse.a
PARSE_DIR = ../parsing
PARSE_LIB = $(PARSE_DIR)/$(PARSE)

# EXEC = execution.a
# EXEC_DIR = ./execution
# EXEC_LIB = $(EXEC_DIR)/$(EXEC)

MAKE_LIBR = make --no-print-directory -C

all: $(PARSE_LIB) $(NAME)

$(NAME): $(BUILTINS_OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(BUILTINS_OBJS) $(PARSE_LIB)


$(PARSE_LIB):
	@$(MAKE_LIBR) $(PARSE_DIR)

clean:
	@$(RM) $(BUILTINS_OBJS)
	@$(MAKE_LIBR) $(PARSE_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIBR) $(PARSE_DIR) fclean

re: fclean all
