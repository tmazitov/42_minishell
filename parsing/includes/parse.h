/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:37 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/19 03:53:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define AND_IF		"&&"
# define AMPS_AND	"&"
# define OR_IF		"||"
# define DSEMI		";;"
# define DLESS		"<<"
# define LESSAND	"<&"
# define DGREAT		">>"
# define GREATAND	">&"
# define LESSGREAT	"<>"
# define DLESSDASH	"<<-"
# define CLOBBER	">|"
# define LBRACE 	"{"
# define RBRACE		"}"
# define LPARAN		"("
# define RPARAN		")"
# define D_SIGN		"$"

typedef enum tokentype
{
	WORD,
	PIPE,
	SEMICOLON,
	REDIR,
	END
}	t_tokentype;

typedef struct tokens
{
	t_tokentype		type;
	char			*value;
	struct tokens	*next;
}	t_tokens;

typedef struct astnodes
{
	char			*value;
	struct astnodes	*left;
	struct astnodes	*right;
}	t_astnodes;

typedef struct splitvalutes
{
	char	**out;
	int		index;
	int		offset;
	int		token_count;
}	t_splitvalues;

// ############################## OPEN SH #################################

bool		ft_check_args(char **str_split);
bool		ft_checkshfile(char *str);
bool		ft_checkiffile(char	*str);
bool		check_fd(char *str);
void		ft_openshfile(char *str_input);

// ############################### PARSE ##################################

t_astnodes	*parse_input(char *str);

int			ft_checknextchar(char *c, int index);
int			ft_checknextcharb(char *c, int index);
int			ft_checknextcharc(char *c, int index);

int			ft_strlen_dp(char **s);
void		free_pointer(char **s);
void		print_tokens(t_tokens *head);
char		*enum_word(t_tokentype tokentype);
int			ft_checkcbrackets(char *str);

char		**ft_splittoken(char *str);
char		**ft_handlestring(char **in, char *str, \
			int *index, int token_count);
char		**ft_handlequotes(char **in, char *str, \
			int *index, int token_count);
char		*ft_assignstring(char *str, int start, int end);
char		**ft_realloc_dp(char **s, char *input, int len);

char		*ft_checkoperator(char *c);
char		*ft_tokenize(char *out, char *c, int len);
bool		ft_checkpid(char *c, int index, int offset);
int			ft_handleredir(char *out, char *c, int index, int offset);
int			ft_handleoper(char *out, char *c, int index, int offset);

char		**str_token(char **str);
char		**ft_handletokens(char **outdp, char *str);
t_tokens	*tokenize_input(char **str_token);
char		*ft_token_value(char *str_token);
t_tokens	*ft_sethead_token(t_tokens *head, t_tokens *tail, t_tokens *token);

t_astnodes	*ft_parsetokens(t_tokens **tokens);
t_astnodes	*parse_command(t_tokens **tokens);
char		*merge_string(char *s1, char *s2);
void		print_ast(t_astnodes *rootnode, int depth);

// ############################# GRAMMAR #################################

bool		ft_shellgrammar(t_tokens *tokens);
bool		ft_completecommand(t_tokens *tokens);
bool		ft_checkpipe(t_tokens *tokens);
bool		ft_ioredir(t_tokens *token_start, t_tokens *token_end);
bool		ft_checkstart(t_tokens *tokens);

bool		ft_checkparam(t_tokens *tokens);
bool		ft_checksyntax(t_tokens *tokens);
bool		ft_checkparenthesis(t_tokens *tokens);
int			ft_checksquotes(char *str);
int			ft_checkdquotes(char *str);
#endif