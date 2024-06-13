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
	t_varlist	*var_head;

	var_head = *varnames;
	while (*varnames != NULL && (*varnames)->varname != NULL)
	{
		ft_printf("varname: %s || value: %s\n", (*varnames)->varname, \
			(*varnames)->value);
		(*varnames) = (*varnames)->next;
	}
	*varnames = var_head;
}

t_varlist	*ft_init_var(void)
{
	t_varlist	*var;

	var = ft_create_var(NULL, NULL);
	return (var);
}

t_varlist	*ft_create_var(char *varname, char *varvalue)
{
	t_varlist	*varnames;

	varnames = (t_varlist *)malloc(sizeof(t_varlist));
	varnames->varname = varname;
	varnames->value = varvalue;
	varnames->next = NULL;
	return (varnames);
}

t_envlist	*ft_init_env(char **envp)
{
	int			count;
	char		**var_split;
	t_envlist	*var;
	t_envlist	*curr_var;
	t_envlist	*envlist;

	count = 0;
	if (!*envp)
		return (NULL);
	var_split = ft_split(envp[count++], '=');
	if (ft_strlen_dp(var_split) > 2)
		var_split = ft_merge_envvalues(var_split);
	var = ft_create_env(var_split, var_split[0], var_split[1]);
	envlist = var;
	while (envp[count] != NULL)
	{
		var_split = ft_split(envp[count++], '=');
		if (ft_strlen_dp(var_split) > 2)
			var_split = ft_merge_envvalues(var_split);
		curr_var = ft_create_env(var_split, var_split[0], var_split[1]);
		var->next = curr_var;
		var = var->next;
	}
	return (envlist);
}

char	*ft_env_to_string(t_envlist *envlist)
{
	char	*env_name;
	char	*env_string;

	if (!envlist)
		return (NULL);
	env_name = ft_strjoin(envlist->varname, "=");
	if (!env_name)
		return (NULL);
	if (!envlist->value || ft_strlen(envlist->value) == 0)
		return (env_name);
	env_string = ft_strjoin(env_name, envlist->value);
	free(env_name);
	return (env_string);
}

// t_sorted_envlist  *ft_init_sortedenv(char **envp)
// {
// 	int			        count;
// 	char		        **var_split;
// 	t_sorted_envlist	*var;
// 	t_sorted_envlist	*curr_var;
//     t_sorted_envlist    *envlist;

// 	count = 0;
//     if (!*envp)
//         return (NULL);
//     var_split = ft_split(envp[count++], '=');
//     if (ft_strlen_dp(var_split) > 2)
//         var_split = ft_merge_envvalues(var_split);
//     var = ft_create_sortedenv(var_split[0], var_split[1]);
// 	envlist = var;
// 	while (envp[count] != NULL)
// 	{
// 		var_split = ft_split(envp[count++], '=');
//         if (ft_strlen_dp(var_split) > 2)
//             var_split = ft_merge_envvalues(var_split);
// 		curr_var = ft_create_sortedenv(var_split[0], var_split[1]);
// 		var->next = curr_var;
// 		var = var->next;
// 	}
//     return (envlist);
// }

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