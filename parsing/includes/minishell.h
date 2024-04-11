/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:37 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 03:17:06 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef enum nodetype
{
	s_cmnd,
	c_cmnd,
	ppln,
	rdrn,
	io_file,
	io_here,
	argmnt,
	errmsg,
}	t_nodetype;

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

typedef struct ast_node
{
	t_nodetype			ntype;
	char				*value;
	char				*errmsg;
	struct ast_node		**child;
	size_t				num_child;
}	t_astnode;

void		ft_printstr(char **str_split);
int			strsplit_count(char **str_split);
void		ft_freesplit(char **str);

void		parse_input(char *str);

t_astnodes	*ft_parsetokens(t_tokens **tokens);
t_astnodes	*parse_command(t_tokens **tokens);
char		*merge_string(char *s1, char *s2);
void		print_ast(t_astnodes *rootnode, int depth);

bool		ft_shellgrammar(t_tokens *tokens);
bool		ft_checkstart(t_tokens *tokens);
bool		ft_checkparam(t_tokens *tokens);
bool		ft_checksyntax(t_tokens *tokens);
bool		ft_checkparenthesis(t_tokens *tokens);
bool		ft_completecommand(t_tokens *tokens);
bool		ft_checkpipe(t_tokens *tokens);
bool		ft_ioredir(t_tokens *token_start, t_tokens *token_end);

void		free_ast(t_astnode *root);
void		skip_whitespace(const char **cmnd);
int			strsplit_size(char **str);
char		*ft_checkoperator(char *c);
char		*ft_tokenize(char *out, char *c, int len);
bool		ft_checkpid(char *c, int index, int offset);
int			ft_checknextchar(char *c, int index);
int			ft_checknextcharb(char *c, int index);
int			ft_checknextcharc(char *c, int index);
int			ft_handleredir(char *out, char *c, int index, int offset);
int			ft_handleoper(char *out, char *c, int index, int offset);
int			ft_checksquotes(char *str);
int			ft_checkdquotes(char *str);
int			ft_checkcbrackets(char *str);
char		**ft_splittoken(char *str);
char		*ft_assignstring(char *str, int start, int end);
char		**ft_realloc_dp(char **s, char *input, int len);
int			ft_strlen_dp(char **s);
void		free_pointer(char **s);
char		**ft_handlestring(char **in, char *str, \
			int *index, int token_count);
char		**ft_handlequotes(char **in, char *str, \
			int *index, int token_count);
int			get_indexquotes(char *str, int index);
int			get_indexstring(char *str, int index);

void		printout(char **out);
char		**str_token(char **str);
char		**ft_handletokens(char **outdp, char *str);

t_tokens	*ft_sethead_token(t_tokens *head, t_tokens *tail, t_tokens *token);
t_tokens	*tokenize_input(char **str_token);
void		print_tokens(t_tokens *head);
char		*enum_word(t_tokentype tokentype);
#endif