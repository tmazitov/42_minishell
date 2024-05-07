# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 21:27:48 by tmazitov          #+#    #+#              #
#    Updated: 2024/05/07 11:54:22 by emaravil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME		=	pipex.a
CC			=	cc
LB			=	ar rcs
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
CHAN_SRCS	=	chan/chan.c \
				chan/close.c \
				chan/free.c
CHAN_OBJ	=	$(CHAN_SRCS:.c=.o)

SRC_SRCS	=	src/com_exec_path.c \
				src/com_exec.c \
				src/com_queue_node.c \
				src/com_queue_utils.c \
				src/com_queue.c \
				src/input.c \
				src/output.c
SRC_OBJ		=	$(SRC_SRCS:.c=.o)

UTILS_SRCS	=	utils/utils.c \
				utils/find_command.c \
				utils/ft_split.c \
				utils/ft_strnstr.c

UTILS_OBJ	=	$(UTILS_SRCS:.c=.o)

HEADER		=	src/pipex.h \
				chan/chan.h \
				utils/utils.h \
				bonus/main_bonus.h \
				get_next_line/get_next_line.h

MAND_SRCS	=	mandatory/mandatory.c
MAND_OBJS	=	$(MAND_SRCS:.c=.o)

BONUS_SRCS	=	bonus/heredoc_bonus.c \
				bonus/output_bonus.c \
				bonus/main_bonus.c
BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

LIBFT		=	../../libft/libft.a

#COMMANDS
%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

# $(NAME): $(UTILS_OBJ) $(CHAN_OBJ) $(SRC_OBJ) $(MAND_OBJS)
# 	@$(LB) $(NAME) $(UTILS_OBJ) $(CHAN_OBJ) $(SRC_OBJ) $(MAND_OBJS)
# 	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all: $(NAME)

$(NAME): $(UTILS_OBJ) $(CHAN_OBJ) $(SRC_OBJ)
	@$(LB) $(NAME) $(UTILS_OBJ) $(CHAN_OBJ) $(SRC_OBJ)
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)" 

clean:
	@$(RM) $(UTILS_OBJ)
	@$(RM) $(CHAN_OBJ)
	@$(RM) $(SRC_OBJ)
	@$(RM) $(MAND_OBJS)
	@echo "$(YELLOW) pipex: OBJECT FILES DELETED!$(DEFAULT)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED) pipex: LIBRARY AND OBJECTS DELETED!$(DEFAULT)"

re: fclean all

.PHONY:		all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
