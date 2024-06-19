/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:02:33 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 05:27:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_selectmode(char c, char mode)
{
	if (c == '\'' && mode == 1)
		mode = '\'';
	else if (c == '\'' && mode == '\'')
		mode = 1;
	else if (c == '\"' && mode == '\"')
		mode = 1;
	else if (c == '\"' && mode == 1)
		mode = '\"';
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
	char		*varvalue;
	char		currdir[PATH_MAX];
	char		*oldpwd;
	static int	pwd_stat;

	if (ft_checkvarenv("PWD", envlist))
		pwd_stat = 0;
	if (varname == NULL && out == NULL)
		return (NULL);
	varvalue = ft_getenv(varname, envlist, varlist);
	oldpwd = ft_getenv("OLDPWD", envlist, varlist);
	if (ft_compname(varname, "PWD") && !ft_checkvarenv("PWD", envlist) \
		&& pwd_stat == 0 && (!oldpwd || !*oldpwd))
		pwd_stat = 1;
	if (ft_compname(varname, "PWD") && !ft_checkvarenv("PWD", envlist) \
		&& pwd_stat == 1)
		varvalue = getcwd(currdir, sizeof(currdir));
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
