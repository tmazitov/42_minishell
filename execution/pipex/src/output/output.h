/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:48:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/11 10:04:18 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "../../../../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef enum {
	OUTFILE = 3,
}		t_output_dest;

typedef struct	s_com_output {
	t_output_dest	src;
	int				fd;
	char			*filepath;
	char			*limiter;
}		t_com_output;

typedef struct	s_com_output_storage
{
	int				file_amount;
	int				total_amount;
	t_com_output	**content;
}		t_com_output_storage;

// Outfile

t_com_output	*make_file_output(char *filepath);
void			*free_file_output(t_com_output *output);

// Output storage

t_com_output_storage	*make_output_storage(char **com_line);
void					close_all_output(t_com_output_storage *st);
void					*free_output_storage(t_com_output_storage *st);
int						remove_com_line_output(char **com);
t_com_output			*get_last_output(t_com_output_storage *storage);
int						fill_output_storage(t_com_output_storage *st, char *com_string);
#endif