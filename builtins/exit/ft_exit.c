/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 15:26:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_exit(char *str, t_builtin_info *info)
{
	char	**str_split;
	int		exit_status;

	exit_status = 0;
	str_split = ft_split(str, ' ');
	ft_printf("exit\n");
	if (ft_strlen_dp(str_split) > 2)
		return (ft_printf("bash: exit: too many arguments\n"), 1);
	if (ft_strlen_dp(str_split) == 2)
	{
		exit_status = exit_status_out(str_split);
		exit_status = check_exitstatus(exit_status);
	}
	free_pointer(str_split);
	free_queue(info->q);
	ft_free_env(info->env);
	ft_free_var(info->var);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (exit_status);
	return (exit_status);
}

int	exit_status_out(char **c)
{
	int		count;
	int		sign;
	int64_t result;
	int64_t temp;

	count = 0;
	sign = 1;
	temp = 0;
	result = 0;
	if (c[1][count] == '-' || c[1][count] == '+')
		if (c[1][count++] == '-')
			sign *= -1;
	while (c[1] != NULL && c[1][count])
	{
		if (ft_isdigit(c[1][count]) == 0)
			return (ft_printf("bash: exit: %s: numeric argument required\n", \
				c[1]), 255);
		temp = (temp * 10) + (sign * (c[1][count++] - '0'));
		if ((temp > result && (sign < 0)) || (temp < result && (sign > 0)))
			return (ft_printf("bash: exit: %s: numeric argument required\n", \
				c[1]), 255);
		result = temp;
	}
	return (result);
}

int	check_exitstatus(int n)
{
	if (n >= 0 && n <= 256)
		return (n % 256);
	if (n > 0)
	{
		while (n % 256 > 256)
			n = n % 256;
		return (n);
	}
	else if (n < 0)
	{
		while (n % 256 < -256)
			n = n % 256;
		return (n);
	}
	else
		return (0);
}
