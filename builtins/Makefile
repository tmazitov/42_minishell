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

NAME			= 	builtins.a
CC				= 	cc
FLAGS			= 	-Wall -Wextra -Werror
RM				= 	rm -rf
LB				= 	ar rcs
LDFLAGS			=	-L../libft -lft

BUILTINS_SRCS	=	./echo/ft_echo.c \
					./main.c \
					./utils/echo_utils.c \
					./utils/env_utils.c \
					./env/ft_setvar.c \
					./env/ft_unsetvar.c \
					./export/ft_export.c \
					./builtins.c
BUILTINS_OBJS	=	$(BUILTINS_SRCS:.c=.o)
HEADER			=	./builtins.h

PARSE			= parse.a
PARSE_DIR		= ../parsing
PARSE_LIB		= $(PARSE_DIR)/$(PARSE)

LIBFT			=	libft.a
LIBFT_DIR		=	../libft
LIBFT_LIB		=	$(LIBFT_DIR)/$(LIBFT)

#COMMANDS
# %.o: %.c $(HEADER) Makefile
# 	@${CC} ${FLAGS} -c $< -o $@

MAKE_LIBR = make --no-print-directory -C

all: $(PARSE_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(BUILTINS_OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(BUILTINS_OBJS) $(PARSE_LIB) $(LDFLAGS)

$(LIBFT_LIB):
	@$(MAKE_LIBR) $(LIBFT_DIR)

$(PARSE_LIB):
	@$(MAKE_LIBR) $(PARSE_DIR)

clean:
	@$(RM) $(BUILTINS_OBJS)
	@$(MAKE_LIBR) $(PARSE_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIBR) $(PARSE_DIR) fclean

re: fclean all
