NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address
MINISHELL_SRCS	=	minishell.c \
					parsing/src/parse/ft_parse.c \
					parsing/src/parse/ft_tokenize.c \
					parsing/src/parse/ft_toktoast.c \
					parsing/src/parse/ft_strtoken.c \
					parsing/src/parse/ft_splittoken.c \
					parsing/src/parse/ft_parse_utils.c \
					parsing/src/parse/ft_checknextchar.c \
					parsing/src/grammar/ft_checksyntax.c \
					parsing/src/grammar/ft_checkgrammar.c \
					parsing/src/open_sh/ft_open_sh.c \
					execution/execution.c \
					execution/ast_command_q.c \


MINISHELL_OBJS = $(MINISHELL_SRCS:.c=.o)
# VPATH = parsing:src:includes:lib:parsing/lib/libft:parsing/src/parse:parsing/src/token:parsing/src/grammar:parsing/src/open_sh

LIBFT = libft.a
LIBFT_DIR = ./parsing/lib/libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBR = $(LIBFT_LIB)

PIPEX = pipex.a
PIPEX_DIR = ./execution/pipex
PIPEX_LIB = $(PIPEX_DIR)/$(PIPEX)

MAKE_LIBR = make --no-print-directory -C

RM = rm -rf

LB = ar rcs

all: $(LIBFT_LIB) $(PIPEX_LIB) $(MINISHELL) $(NAME)


$(NAME): $(MINISHELL_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_LIB) $(PIPEX_LIB) $(MINISHELL_OBJS) -o $(NAME) -lreadline

# Make libft archive
$(LIBFT_LIB):
	$(MAKE_LIBR) $(LIBFT_DIR)

# Make pipex archive
$(PIPEX_LIB):
	$(MAKE_LIBR) $(PIPEX_DIR)

clean:
	$(RM) $(MINISHELL_OBJS)
	$(MAKE_LIBR) $(LIBFT_DIR) fclean
	$(MAKE_LIBR) $(PIPEX_DIR) fclean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBR) $(LIBFT_DIR) fclean
	$(MAKE_LIBR) $(PIPEX_DIR) fclean

re: fclean all
