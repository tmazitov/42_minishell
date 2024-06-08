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
# LDFLAGS			=	-L../libft -lft

BUILTINS_SRCS	=	./echo/ft_echo.c \
					./utils/cd_utils.c \
					./utils/echo_utils.c \
					./utils/env_utils.c \
					./utils/export_utils.c \
					./utils/sortenv_utils.c \
					./utils/ft_free_env.c \
					./utils/ft_free_sortedenv.c \
					./utils/ft_free_var.c \
					./cd/ft_cd.c \
					./env/ft_setvar.c \
					./env/ft_unsetvar.c \
					./env/ft_env.c \
					./pwd/ft_pwd.c \
					./export/ft_export.c \
					./exit/ft_exit.c \
					./builtins_utils.c \
					./com_queue.c \
					./input_storage.c

BUILTINS_OBJS	=	$(BUILTINS_SRCS:.c=.o)
HEADER			=	./builtins.h

# PARSE			= parse.a
# PARSE_DIR		= ../parsing
# PARSE_LIB		= $(PARSE_DIR)/$(PARSE)

# LIBFT			=	libft.a
# LIBFT_DIR		=	../libft
# LIBFT_LIB		=	$(LIBFT_DIR)/$(LIBFT)

#COMMANDS
%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

MAKE_LIBR = make --no-print-directory -C

all: $(NAME)

# $(NAME): $(BUILTINS_OBJS)
# 	@$(CC) $(CFLAGS) -o $(NAME) $(BUILTINS_OBJS) $(PARSE_LIB) $(LDFLAGS)

$(NAME): $(BUILTINS_OBJS)
	@$(LB) $(NAME) $(BUILTINS_OBJS)
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"

# $(LIBFT_LIB):
# 	@$(MAKE_LIBR) $(LIBFT_DIR)

# $(PARSE_LIB):
# 	@$(MAKE_LIBR) $(PARSE_DIR)

clean:
	@$(RM) $(BUILTINS_OBJS)
	@echo "$(YELLOW) builtins: OBJECT FILES DELETED!$(DEFAULT)"
# @$(MAKE_LIBR) $(PARSE_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) builtins: LIBRARY FILE DELETED!$(DEFAULT)"
# @$(MAKE_LIBR) $(PARSE_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m