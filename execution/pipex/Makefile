# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 21:27:48 by tmazitov          #+#    #+#              #
#    Updated: 2024/04/25 01:47:04 by marvin           ###   ########.fr        #
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
				chan/free.c \
				chan/payload.c
CHAN_OBJ	=	$(CHAN_SRCS:.c=.o)

GNL_SRCS	=	get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
GNL_OBJ		=	$(GNL_SRCS:.c=.o)

SRC_SRCS	=	src/com_exec.c \
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

PRINTF_SRCS	= 	printf/ft_puthex.c \
				printf/ft_putchar.c \
				printf/ft_putstr.c \
				printf/ft_putnbr.c \
				printf/ft_putunbr.c
PRINTF_OBJS =	$(PRINTF_SRCS:.c=.o)

HEADER		=	src/pipex.h \
				chan/chan.h \
				utils/utils.h \
				bonus/main_bonus.h \
				printf/ft_printf.h \
				get_next_line/get_next_line.h

MAND_SRCS	=	mandatory/mandatory.c
MAND_OBJS	=	$(MAND_SRCS:.c=.o)

BONUS_SRCS	=	bonus/heredoc_bonus.c \
				bonus/output_bonus.c \
				bonus/main_bonus.c
BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

#COMMANDS
# %.o: %.c $(HEADER) Makefile
# 	@${CC} ${FLAGS} -c $< -o $@

# $(NAME): $(UTILS_OBJ) $(GNL_OBJ) $(PRINTF_OBJS) $(CHAN_OBJ) $(SRC_OBJ) $(MAND_OBJS)
# 	@$(LB) $(NAME) $(UTILS_OBJ) $(GNL_OBJ) $(PRINTF_OBJS) $(CHAN_OBJ) $(SRC_OBJ) $(MAND_OBJS)
# 	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all: $(NAME)

$(NAME): $(UTILS_OBJ) $(GNL_OBJ) $(CHAN_OBJ) $(SRC_OBJ) $(PRINTF_OBJS)
	@$(LB) $(NAME) $(UTILS_OBJ) $(GNL_OBJ) $(PRINTF_OBJS) $(CHAN_OBJ) $(SRC_OBJ) 
	@echo "$(GREEN) $(NAME) :: LIBRARY CREATED!$(DEFAULT)"

clean:
	@$(RM) $(UTILS_OBJ)
	@$(RM) $(GNL_OBJ)
	@$(RM) $(CHAN_OBJ)
	@$(RM) $(SRC_OBJ)
	@$(RM) $(PRINTF_OBJS)
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
