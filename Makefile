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

UNAME		=	$(shell uname)
NAME			= 	minishell
CC				= 	cc
# FLAGS			= 	-Wall -Wextra -Werror -g -I $(LIBREAD_INC)
RM				= 	rm -rf
LB				= 	ar rcs
LDFLAGS			=	-L./libft -lft

MINISHELL_SRCS	=	minishell.c
MINISHELL_OBJS 	=	$(MINISHELL_SRCS:.c=.o)
HEADER			= 	minishell.h

PARSE			=	parse.a
PARSE_DIR		=	./parsing
PARSE_LIB		=	$(PARSE_DIR)/$(PARSE)

BUILTINS		=	builtins.a
BUILTINS_DIR	=	./builtins
BUILTINS_LIB	=	$(BUILTINS_DIR)/$(BUILTINS)

EXEC			=	execution.a
EXEC_DIR		=	./execution
EXEC_LIB		=	$(EXEC_DIR)/$(EXEC)

LIBFT			=	libft.a
LIBFT_DIR		=	./libft
LIBFT_LIB		=	$(LIBFT_DIR)/$(LIBFT)

# LIBREAD_DIR		=	/usr/local/Cellar/readline/8.2.10/lib
# LIBREAD_INC		=	/usr/local/Cellar/readline/8.2.10/include/readline
# LIBREAD_DIR		:= $(shell find /usr/local -name 'libreadline.a' -exec dirname {} \;)
# LIBREAD_INC		:= $(shell find /usr/local -name 'readline.h' -exec dirname {} \;)

MAKE_LIBR		= 	make --no-print-directory -C

%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

all: $(LIBFT_LIB) $(PARSE_LIB) $(BUILTINS_LIB) $(EXEC_LIB) $(NAME)

ifeq ($(UNAME), Darwin)
FLAGS			= 	-Wall -Wextra -Werror -g -I $(LIBREAD_INC)
LIBREAD_DIR		:= $(shell find /usr/local -name 'libreadline.a' -exec dirname {} \;)
LIBREAD_INC		:= $(shell find /usr/local -name 'readline.h' -exec dirname {} \;)
$(NAME): $(MINISHELL_OBJS)
	@$(CC) $(FLAGS) $(MINISHELL_OBJS) $(PARSE_LIB) $(EXEC_LIB) $(BUILTINS_LIB) $(LDFLAGS) -L$(LIBREAD_DIR) -lreadline -o $(NAME) 
else ifeq ($(UNAME), Darwin)
FLAGS			=	-Wall -Wextra -Werror -g
$(NAME): $(MINISHELL_OBJS)
	@$(CC) $(FLAGS) $(MINISHELL_OBJS) $(PARSE_LIB) $(EXEC_LIB) $(BUILTINS_LIB) $(LDFLAGS) -lreadline -o $(NAME) 
endif

# Make libft archive
$(BUILTINS_LIB):
	@$(MAKE_LIBR) $(BUILTINS_DIR)

$(LIBFT_LIB):
	@$(MAKE_LIBR) $(LIBFT_DIR)

# Make parse archive
$(PARSE_LIB):
	@$(MAKE_LIBR) $(PARSE_DIR)

# Make execution archive
$(EXEC_LIB):
	@$(MAKE_LIBR) $(EXEC_DIR)

clean:
	@$(RM) $(MINISHELL_OBJS)
	@$(MAKE_LIBR) $(BUILTINS_DIR) clean
	@$(MAKE_LIBR) $(LIBFT_DIR) clean
	@$(MAKE_LIBR) $(PARSE_DIR) clean
	@$(MAKE_LIBR) $(EXEC_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIBR) $(BUILTINS_DIR) fclean
	@$(MAKE_LIBR) $(LIBFT_DIR) fclean
	@$(MAKE_LIBR) $(PARSE_DIR) fclean
	@$(MAKE_LIBR) $(EXEC_DIR) fclean

re: fclean all
