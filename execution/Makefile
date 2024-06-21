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
NAME		=	execution.a
CFLAGS			=	-Wall -Wextra -Werror -I /Users/emaravil/.local/opt/readline/include
CC			= 	cc
RM			=	rm -rf
LB			= 	ar rcs

EXEC_SRCS	=	./src/execution.c \
				./src/execution_utils.c \
				./src/ast_utils.c \
				./src/ast_command.c \
				./src/ast_command_q.c \
				./src/ast_command_utils.c \
				./src/ast_command_builtin.c 
				
EXEC_OBJS	=	$(EXEC_SRCS:.c=.o)

HEADER		=	./includes/execution.h

PIPEX = pipex.a
PIPEX_DIR = ./pipex
PIPEX_LIB = $(PIPEX_DIR)/$(PIPEX)

SIGNALS = signals.a
SIGNALS_DIR = ./signals
SIGNALS_LIB = $(SIGNALS_DIR)/$(SIGNALS)

MAKE_LIBR 	=	make --no-print-directory -C

all: $(PIPEX_LIB) $(SIGNALS_LIB) $(NAME)

$(PIPEX_LIB):
	@$(MAKE_LIBR) $(PIPEX_DIR)

$(SIGNALS_LIB):
	@$(MAKE_LIBR) $(SIGNALS_DIR)

ifeq ($(UNAME), Linux)
$(NAME): $(EXEC_OBJS)
	@mkdir -p extracted_objs
	@ar x $(SIGNALS_LIB) --output=extracted_objs
	@ar x $(PIPEX_LIB) --output=extracted_objs
	@$(LB) $(NAME) $(EXEC_OBJS) extracted_objs/*o
	@$(RM) extracted_objs
	@echo	"$(GREEN) $(NAME):: LIBRARY CREATED!$(DEFAULT)"
else ifeq ($(UNAME), Darwin)
$(NAME): $(PIPEX_LIB) $(SIGNALS_LIB) $(EXEC_OBJS)
	@libtool -static -o $@ $^
	@echo	"$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"
endif

clean:
	@$(RM) $(EXEC_OBJS)
	@echo "$(YELLOW) execution: OBJECT FILES DELETED!$(DEFAULT)"
	@$(MAKE_LIBR) $(PIPEX_DIR) clean

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED) execution: LIBRARY FILE DELETED!$(DEFAULT)"
	@$(RM) $(PIPEX_LIB)
	@echo "$(RED) pipex: LIBRARY FILE DELETED!$(DEFAULT)"
	@$(RM) $(SIGNALS_LIB)
	@echo "$(RED) pipex: LIBRARY FILE DELETED!$(DEFAULT)"

re: fclean all

.PHONY: all bonus clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m