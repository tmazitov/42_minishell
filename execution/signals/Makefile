# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 18:13:05 by tmazitov          #+#    #+#              #
#    Updated: 2024/05/09 15:44:36 by emaravil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#SETUP
NAME		=	signals.a
CC			=	cc
LB			=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror -I /Users/emaravil/.local/opt/readline/include
RM			=	rm -rf

#FILES AND PATH

SRC_SRCS	=	src/signals.c \
				src/status.c

SRC_OBJ		=	$(SRC_SRCS:.c=.o)

# %.o: %.c $(HEADER) Makefile
# 	${CC} ${FLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(SRC_OBJ)
	@$(LB) $(NAME) $(SRC_OBJ) 
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"

clean:
	@$(RM) $(SRC_OBJ)
	@echo "$(YELLOW) pipex: OBJECT FILES DELETED!$(DEFAULT)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED) pipex: LIBRARY AND OBJECTS DELETED!$(DEFAULT)"

re: fclean all

.PHONY:		all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
