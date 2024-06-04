/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:51 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../parsing/includes/parse.h"
# include <string.h>
# include "../execution/pipex/chan/chan.h"
# include "../execution/pipex/src/input/input.h"
# include "../execution/pipex/src/output/output.h"

typedef struct s_com_node
{
	char					*name;
	char					*path;
	char					*builtin;
	char					**args;
	struct s_com_node		*next;
	struct s_com_node		*prev;
	t_log_chan				*in_chan;
	t_log_chan				*out_chan;
	t_com_output_storage	*output;
	t_com_input_storage		*input;
	int						proc_id;
	int						proc_status;
}		t_com_node;

typedef struct s_com_queue
{
	t_com_node	*nodes;
	t_com_node	*first;
	int			chan_closed;
}		t_com_queue;

typedef struct varlist
{
	char			*value;
	char			*varname;
	struct varlist	*next;
}	t_varlist;

typedef struct envlist
{
	char			*value;
	char			*varname;
	struct envlist	*next;
}	t_envlist;

typedef struct sorted_envlist
{
	char					*value;
	char					*varname;
	struct sorted_envlist	*next;
}	t_sorted_envlist;

typedef struct builtin_info
{
	t_envlist	**env;
	t_varlist	**var;
	t_com_queue	*q;
}		t_builtin_info;


void		ft_echo(char *str, t_envlist *envlist, t_varlist *varlist);
void		ft_printparams(char *str, char *cmd_split, t_envlist *envlist, t_varlist *varlist);
void		ft_printdquotes(char *str, t_envlist *envlist, t_varlist *varlist);
void		ft_printexpansion(char *str, int index, t_envlist *envlist, t_varlist *varlist);
void		ft_printsquotes(char *str);
bool		ft_checkvarname(char *varname);
char		*ft_getvarname(char *str, int index);
int			ft_countvarname(char *varname);
char		*ft_getenv(char *varname, t_envlist *envlist, t_varlist *varlist);

int			ft_setvar(char *str, t_envlist **envlist, t_varlist **varlist);
int			ft_setvarname(char *str, t_envlist **envlist, t_varlist **varlist);
char		**ft_handlesetvarsplit(char *str, char **var);
char		*ft_splitvarvalue(char *start, t_envlist **envlist, t_varlist **varlist);
char		*ft_copyvarvalues(char *s1, char *s2, size_t len1, size_t len2);
char		*ft_mergevarval(char *str, char *s1, char *s2);
char		*ft_getvaluesquotes(char *str);
char		*ft_getvaluedquotes(char *str, t_envlist **envlist, t_varlist **varlist);
char		*ft_splitequalsign(char *start, char *end, t_envlist **envlist, t_varlist **varlist);
char		*ft_expanddquotes(char *str, int len, t_envlist **envlist, t_varlist **varlist);
int			ft_unsetvarname(char *str, t_envlist **envlist, t_varlist **varlist);
int			ft_setenvlist(char *varname, char *varvalue, int overwrite, t_envlist **envlist);
int			ft_setvarlist(char *varname, char *varvalue, int overwrite, t_varlist **varlist);
int			ft_unsetenv(char *varname, t_envlist **envlist, t_varlist **varlist);
int			ft_unsetvar(char *varname, t_varlist **varlist);
t_varlist	*ft_init_var();
t_varlist	*ft_create_var(char *varname, char *varvalue);
void		ft_printenvp(char **envp);
void		ft_printvar(t_varlist **varnames);

t_envlist  	*ft_init_env(char **envp);
t_envlist	*ft_create_env(char **var_split, char *varname, char *varvalue);
char		**ft_env_converter(t_envlist **envlist);
void		*free_envlist(t_envlist *envlist);

void		ft_printenv(t_envlist *envlist, t_varlist *varlist);
// char 		**ft_merge_envvalues(char **var_split, char *str);
char		**ft_merge_envvalues(char **var_split);
char		*ft_copyvalues(char **var_split, char *var_newsplit);

int			ft_export(char *str, t_envlist **envlist, t_varlist **varlist);
int			ft_checkexport(char *varname, char *str_input, t_envlist **envlist, \
			t_varlist **varlist);
char		**ft_handleexportsplit(char *str, char **var);
char		*ft_splittoname(char *str, t_envlist **envlist, t_varlist **varlist);
void		ft_exportvar(char *varname, t_envlist **envlist, t_varlist **varlist);
void		ft_printexport(t_envlist **envlist, t_varlist **varlist);
bool		ft_checkvarenv(char *varname, t_envlist *envlist);
bool		ft_checkvarlist(char *varname, t_varlist *varlist);

void		ft_copyenvlist();

t_sorted_envlist	*ft_create_sortedenv(char *varname, char *varvalue);
t_sorted_envlist	*ft_init_sortedenv(t_envlist **envlist);
t_sorted_envlist    *ft_sortenvlist(t_sorted_envlist *sorted_envlist);
t_sorted_envlist	*insertsortedlist(t_sorted_envlist *head, t_sorted_envlist *newnode);

int			ft_builtins(char *str, t_builtin_info *info);
bool    	ft_checkcmd(char *str);

void	ft_pwd(char *str);

int		ft_cd(char *path, t_envlist **envlist, t_varlist **varlist);
char	**ft_handlecdsplit(char *str, char **var);
char	*ft_cdexpandpath(char *pathstr, t_envlist **envlist, t_varlist **varlist);
int		ft_update_envlist(char *path, char *currdir, t_envlist **envlist);
char	*ft_getpath(char *str, t_envlist **envlist, t_varlist **varlist);
char	*ft_expandhomepath(char **path_split, t_envlist *envlist, t_varlist *varlist);
char	*ft_copystring(char *str);

void		ft_exit(char *str, t_builtin_info *info);
void		*free_queue(t_com_queue *queue);
t_com_node	*get_first(t_com_queue *q);
void		*free_queue_relationship(t_com_queue *queue);
void		ft_free_var(t_varlist **varlist);
void		ft_free_env(t_envlist **envlist);
void		ft_free_sortedenv(t_sorted_envlist **sorted_envlist);
#endif //BUILTINTS_H

//$0 – The name of the Bash script.
// $1 to $9 – The first 9 arguments to the Bash script.
// $# – The number of arguments supplied to the Bash script.
// $@ – All the arguments supplied to the Bash script.
// $? – The exit status of the last command executed.