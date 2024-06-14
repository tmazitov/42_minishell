/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:02:33 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/14 13:23:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_selectmode(char c, int mode)
{
	if (c == '\'' && mode == 1)
		mode = 0;
	else if (c == '\'' && mode == 0)
		mode = 1;
	return (mode);
}

char	*ft_mergedollar_a(char *str, char *out, int count)
{
	size_t	outlen;

	out = ft_realloc(out, ft_strlen(out) + 2);
	outlen = ft_strlen(out);
	out[outlen] = str[count];
	out[outlen + 1] = '\0';
	return (out);
}

char	*ft_mergedollar_b(char	*varname, char *out, t_envlist *envlist, \
	t_varlist *varlist)
{
	char	*varvalue;

	varvalue = ft_getenv(varname, envlist, varlist);
	if (varvalue != NULL && *varvalue)
		out = ft_mergevarval(NULL, out, varvalue);
	return (out);
}

bool	user_input_is_valid(char *user_input)
{
	return ((bool)(user_input
		&& ft_strlen(user_input) > 0
		&& *user_input != '\0'));
}

bool	is_sh_file(char *user_input)
{
	return ((bool)ft_checkshfile(user_input));
}
