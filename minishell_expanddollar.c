/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expanddollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:08:56 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 05:31:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expanddollar(char *str, t_builtin_info *info)
{
	int		count;
	char	*out;
	char	mode;

	out = (char *)ft_calloc(1, sizeof(char));
	if (out == NULL)
		return (NULL);
	count = 0;
	mode = 1;
	while (str[count])
	{
		mode = ft_selectmode(str[count], mode);
		if (str[count] == '$' && mode != '\'' && str[count + 1] != '\"')
		{
			if (ft_expanddollar_cond(str[count + 1]) == 1)
				out = ft_expanddollar_a(out, &count);
			else if (ft_expanddollar_cond(str[count + 1]) == 2)
				out = ft_expanddollar_b(out, &count);
			else if (ft_expanddollar_cond(str[count + 1]) == 3)
				out = ft_expanddollar_c(str, out, &count, info);
		}
		else
			out = ft_mergedollar_a(str, out, count++);
	}
	return (free(str), out);
}

char	*ft_expanddollar_a(char *out, int *count)
{
	char	*str_temp;

	str_temp = ft_itoa(status_code(GET_HISTORY, -1));
	out = ft_mergevarval(NULL, out, str_temp);
	free(str_temp);
	(*count) += 2;
	return (out);
}

char	*ft_expanddollar_b(char *out, int *count)
{
	out = ft_mergevarval(NULL, out, "$");
	(*count)++;
	return (out);
}

char	*ft_expanddollar_c(char *str, char *out, int *count, \
	t_builtin_info *info)
{
	char	*varname;

	varname = ft_getvarname(str, ++(*count));
	if (!varname)
		(*count) += ft_countvarname(&str[*count]);
	else
	{
		out = ft_mergedollar_b(varname, out, *info->env, *info->var);
		(*count) += ft_countvarname(&str[*count]);
	}
	free(varname);
	return (out);
}

int	ft_expanddollar_cond(char c)
{
	if (c == '?')
		return (1);
	else if ((((c) == '\0') || (ft_isspace(c) > 0) || (c != '\"')) \
		&& !(((ft_isdigit(c) > 0) || ((ft_isalpha(c) > 0)) || c == '_')))
		return (2);
	else if ((ft_isspace(c) == 0) && (c != '\"') && ((ft_isdigit(c) > 0) \
		|| ((ft_isalpha(c) > 0)) || c == '_'))
		return (3);
	return (0);
}
