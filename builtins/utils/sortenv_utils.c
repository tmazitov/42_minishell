/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortenv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:11:37 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 14:49:00 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	**ft_merge_envvalues(char **var_split)
{
	int		index;
	int		len_tot;
	char	**var_newsplit;

	index = 1;
	len_tot = 0;
	while (var_split[index] != NULL)
		len_tot += ft_strlen(var_split[index++]);
	var_newsplit = (char **)malloc(sizeof(char *) * 3);
	if (!var_newsplit)
		return (NULL);
	var_newsplit[0] = (char *)malloc(sizeof(char) * \
		(ft_strlen(var_split[0]) + 1));
	ft_strlcpy(var_newsplit[0], var_split[0], ft_strlen(var_split[0]) + 1);
	var_newsplit[1] = (char *)malloc(sizeof(char) * (len_tot + 1));
	if (!var_newsplit[1])
		return (NULL);
	var_newsplit[1] = ft_copyvalues(var_split, var_newsplit[1]);
	var_newsplit[2] = NULL;
	free_pointer(var_split);
	return (var_newsplit);
}

char	*ft_copyvalues(char **var_split, char *var_newsplit)
{
	int	index;
	int	len_tot;
	int	count;

	index = 1;
	len_tot = 0;
	while (var_split[index] != NULL)
	{
		count = 0;
		while (var_split[index][count] != '\0')
			var_newsplit[len_tot++] = var_split[index][count++];
		index++;
	}
	var_newsplit[len_tot] = '\0';
	return (var_newsplit);
}

t_envlist	*ft_create_env(char **var_split, char *varname, char *varvalue)
{
	t_envlist	*varnames;

	varnames = (t_envlist *)malloc(sizeof(t_envlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	if (var_split != NULL)
		free(var_split);
	return (varnames);
}

t_sorted_envlist	*ft_create_sortedenv(char *varname, char *varvalue)
{
	t_sorted_envlist	*varnames;

	varnames = (t_sorted_envlist *)malloc(sizeof(t_sorted_envlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	return (varnames);
}

void	ft_printenvp(char **envp)
{
	int		count;
	char	*result;
	char	**varname;

	count = 0;
	varname = ft_split(envp[0], '=');
	envp[0] = "eli";
	result = getenv(varname[0]);
	ft_printf("%s\n", result);
	ft_printf("%s\n", *envp);
	while (envp[count] != NULL)
	{
		ft_printf("envp: %s\n", envp[count]);
		count++;
	}
}
