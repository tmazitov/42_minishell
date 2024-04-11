NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

MINISHELL_SRCS = minishell.c ft_checksyntax.c ft_tokenize.c\
					ft_strtoken.c ft_checknextchar.c ft_splittoken.c\
					ft_toktoast.c ft_checkgrammar.c ft_open_sh.c\
					ft_parse_utils.c ft_parse.c
MINISHELL_OBJS = $(MINISHELL_SRCS:.c=.o)
VPATH = parsing:src:includes:lib:parsing/lib/libft:parsing/src/parse:parsing/src/token:parsing/src/grammar:parsing/src/open_sh

LIBFT = libft.a
LIBFT_DIR = ./parsing/lib/libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBR = $(LIBFT_LIB)

MAKE_LIBR = make --no-print-directory -C

RM = rm -rf

LB = ar rcs

all: $(LIBFT_LIB) $(MINISHELL) $(NAME)


$(NAME): $(MINISHELL_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_LIB) $(MINISHELL_OBJS) -o $(NAME) -lreadline

$(LIBFT_LIB):
	$(MAKE_LIBR) $(LIBFT_DIR)

clean:
	$(RM) $(MINISHELL_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBR) $(LIBFT_DIR) fclean

re: fclean all
