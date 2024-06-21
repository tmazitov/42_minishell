/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/21 19:11:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_exit(char *str, t_builtin_info *info)
{
	char	**str_split;
	int		exit_status;

	exit_status = 0;
	str_split = ft_split(str, ' ');
	if (ft_strlen_dp(str_split) > 2)
	{
		free_pointer(str_split);
		return (write(2, "exit\nbash: exit: too many arguments\n", 36), 1);
	}
	else if (ft_strlen_dp(str_split) == 2)
	{
		write(2, "exit\n", 5);
		exit_status = exit_status_out(str_split);
		exit_status = check_exitstatus(exit_status);
	}
	else if (ft_strlen_dp(str_split) == 1)
		write(2, "exit\n", 5);
	free_pointer(str_split);
	handle_exitcmd(info);
	return (exit(exit_status), exit_status);
}

void	handle_exitcmd(t_builtin_info *info)
{
	rl_clear_history();
	free_queue(info->q);
	ft_free_env(info->env);
	ft_free_var(info->var);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	exit_status_out(char **c)
{
	int		count;
	int		sign;
	int64_t	result;
	int64_t	temp;

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
			return (ft_err_b("bash: exit: ", c[1], ": numeric argument \
				required\n"), 255);
		temp = (temp * 10) + (sign * (c[1][count++] - '0'));
		if ((temp > result && (sign < 0)) || (temp < result && (sign > 0)))
			return (ft_err_b("bash: exit: ", c[1], ": numeric argument \
				required\n"), 255);
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
