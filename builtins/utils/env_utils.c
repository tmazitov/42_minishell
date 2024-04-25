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

#include "../builtins.h"

void	ft_printvar(t_varlist **varnames)
{
	t_varlist *var_head;

	var_head = *varnames;
	while (*varnames != NULL && (*varnames)->varname != NULL)
	{
		ft_printf("varname: %s || value: %s\n", (*varnames)->varname, (*varnames)->value);
		(*varnames) = (*varnames)->next;
	}
	*varnames = var_head;
}

void	ft_printenv(t_envlist *envlist)
{
	while (envlist != NULL)
	{
		ft_printf("%s=%s\n", envlist->varname, envlist->value);
		envlist = envlist->next;
	}
}

t_varlist  *ft_init_var()
{
	t_varlist	*var;

    var = ft_create_var(NULL, NULL);
    return (var);
}

t_varlist	*ft_create_var(char *varname, char *varvalue)
{
	t_varlist *varnames;

	varnames = (t_varlist *)malloc(sizeof(t_varlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	return (varnames);
}

t_envlist  *ft_init_env(char **envp)
{
	int			count;
	char		**var_split;
	t_envlist	*var;
	t_envlist	*curr_var;
    t_envlist    *envlist;

	count = 0;
    if (!*envp)
        return (NULL);
    var_split = ft_split(envp[count++], '=');
    if (ft_strlen_dp(var_split) > 2)
        var_split = ft_merge_envvalues(var_split);
    var = ft_create_env(var_split[0], var_split[1]);
	envlist = var;
	while (envp[count] != NULL)
	{
		var_split = ft_split(envp[count++], '=');
        if (ft_strlen_dp(var_split) > 2)
            var_split = ft_merge_envvalues(var_split);
		curr_var = ft_create_env(var_split[0], var_split[1]);
		var->next = curr_var;
		var = var->next;
	}
    return (envlist);
}

t_sorted_envlist  *ft_init_sortedenv(char **envp)
{
	int			        count;
	char		        **var_split;
	t_sorted_envlist	*var;
	t_sorted_envlist	*curr_var;
    t_sorted_envlist    *envlist;

	count = 0;
    if (!*envp)
        return (NULL);
    var_split = ft_split(envp[count++], '=');
    if (ft_strlen_dp(var_split) > 2)
        var_split = ft_merge_envvalues(var_split);
    var = ft_create_sortedenv(var_split[0], var_split[1]);
	envlist = var;
	while (envp[count] != NULL)
	{
		var_split = ft_split(envp[count++], '=');
        if (ft_strlen_dp(var_split) > 2)
            var_split = ft_merge_envvalues(var_split);
		curr_var = ft_create_sortedenv(var_split[0], var_split[1]);
		var->next = curr_var;
		var = var->next;
	}
    return (envlist);
}

char **ft_merge_envvalues(char **var_split)
{
    int     index;
    int     len_tot;
    char    **var_newsplit;

    index = 1;
    len_tot = 0;
    while (var_split[index] != NULL)
        len_tot += ft_strlen(var_split[index++]);
    var_newsplit = (char **)malloc(sizeof(char *) * 3);
    if (!var_newsplit)
        return (NULL);
    var_newsplit[0] = (char *)malloc(sizeof(char) * (ft_strlen(var_split[0]) + 1));
    ft_strlcpy(var_newsplit[0], var_split[0], ft_strlen(var_split[0]) + 1);
    var_newsplit[1] = (char *)malloc(sizeof(char) * (len_tot + 1));
    if (!var_newsplit[1])
        return (NULL);
    var_newsplit[1] = ft_copyvalues(var_split, var_newsplit[1]);
    var_newsplit[2] = NULL;
    free_pointer(var_split);
    return (var_newsplit);
}

char *ft_copyvalues(char **var_split, char *var_newsplit)
{
    int index;
    int len_tot;
    int count;

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

t_envlist	*ft_create_env(char *varname, char *varvalue)
{
	t_envlist    *varnames;

	varnames = (t_envlist *)malloc(sizeof(t_envlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	return (varnames);
}

t_sorted_envlist	*ft_create_sortedenv(char *varname, char *varvalue)
{
	t_sorted_envlist    *varnames;

	varnames = (t_sorted_envlist *)malloc(sizeof(t_sorted_envlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	return (varnames);
}


void	ft_printenvp(char **envp)
{
	int	count;
	char *result;
	char **varname;

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


// char **ft_merge_envvalues(char **var_split, char *str)
// {
//     int     index;
//     int     count;
//     char    **var_newsplit;
//     int     start;

//     index = 0;
//     start = index;
//     var_newsplit = (char **)malloc(sizeof(char *) * 3);
//     if (!var_newsplit)
//         return (NULL);
//     while (str[index] != '\0' && str[index] != '=')
//         index++;
//     var_newsplit[0] = (char *)malloc(sizeof(char) * (index + 1));
//     while (start < index)
//     {
//         var_newsplit[0][start] = str[start];
//         start++;
//     }
//     index++;
//     start++;
//     var_newsplit[0][start] = '\0';
//     while (str[index] != '\0' && str[index] != '\n')
//         index++;
//     var_newsplit[1] = (char *)malloc(sizeof(char) * (index - start) + 1);
//     count = 0;
//     while (count < index - start)
//     {
//         var_newsplit[1][count] = str[count + start];
//         count++;
//     }
//     var_newsplit[1][count] = '\0';
//     var_newsplit[2] = NULL;
//     free_pointer(var_split);
//     return (var_newsplit);
// }