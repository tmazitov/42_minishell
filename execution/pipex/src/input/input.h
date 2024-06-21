/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:26:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 20:44:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../pipex.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "../../../signals/includes/signals.h"
# include "../../../../builtins/builtins.h"
# include "../../../../libft/libft.h"

// File input realization

t_com_input			*make_file_input(char *filepath);
void				*free_file_input(t_com_input *input);
int					file_input_open(t_com_input *input);

// Heredoc input realization

t_com_input			*make_heredoc_input(char *limiter);
void				*free_heredoc_input(t_com_input *input);
char				*heredoc_temp_filepath(void);
int					heredoc_fill(t_com_input *heredoc, t_builtin_info info);

// Input storage

t_com_input_storage	*make_input_storage(char **com_string);
int					fill_input_storage(t_com_input_storage *st, \
										char *com_string);
int					remove_com_line_input(char **com);
void				close_all_input(t_com_input_storage *st);
// Utils

t_com_input			*get_last_input(t_com_input_storage *storage);
int					fill_command_heredoc(t_com_input_storage *storage, \
											t_builtin_info info);
int					open_command_infile(t_com_input_storage *storage);
#endif