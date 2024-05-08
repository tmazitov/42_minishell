/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:26:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/08 14:45:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../../../../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../../../signals/includes/signals.h"

typedef enum {
	INFILE = 1,
	HEREDOC = 2,
}		t_input_src;

typedef struct	s_com_input {
	t_input_src	src;
	int			fd;
	char		*filepath;
	char		*limiter;
}		t_com_input;

typedef struct	s_com_input_storage
{
	int				file_amount;
	int				total_amount;
	int				heredoc_amount;
	t_com_input		**content;
}		t_com_input_storage;

// File input realization

t_com_input			*make_file_input(char *filepath);
void				*free_file_input(t_com_input *input);
int					file_input_open(t_com_input *input);

// Heredoc input realization

t_com_input			*make_heredoc_input(char *limiter);
void				*free_heredoc_input(t_com_input *input);
char				*heredoc_temp_filepath();
int					heredoc_fill(t_com_input *heredoc);
// Input storage

t_com_input_storage	*make_input_storage(char **com_string);
void				*free_input_storage(t_com_input_storage *st);
int					fill_input_storage(t_com_input_storage *st, char *com_string);
int					remove_com_line_input(char **com);
void				close_all_input(t_com_input_storage *st);
// Utils

t_com_input			*get_last_input(t_com_input_storage *storage);
int					fill_command_heredoc(t_com_input_storage *storage);
int					open_command_infile(t_com_input_storage *storage);
#endif