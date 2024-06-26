/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:59:14 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:22:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_printstring(t_print *tab, const char *str, int prec);
static int	ft_print_string(t_print *tab, const char *str, int prec);

int	ft_print_s(t_print *tab)
{
	char	*a;
	int		count;
	int		prec;

	prec = tab->prec;
	count = 0;
	if (prec == -1 && !tab->dot)
		prec = INT_MAX;
	else if (prec == -1 && tab->dot)
		prec = 0;
	a = va_arg(tab->args, char *);
	if (!a)
		a = "(null)";
	if (a == (char *)0)
		a = "";
	count = ft_printstring(tab, a, prec);
	return (count);
}

static int	ft_printstring(t_print *tab, const char *str, int prec)
{
	int		n;
	char	*p;
	int		count;

	count = 0;
	n = 0;
	p = (char *)str;
	if (tab->tlen > 0 && !tab->dash)
	{
		while (*p++ && n < prec)
			n++;
		while (n++ < tab->tlen)
		{
			if (ft_checkerror(tab, ' ') < 0)
				return (-1);
			count++;
		}
		n = 0;
		p = (char *)str;
	}
	count += ft_print_string(tab, p, prec);
	return (count);
}

static int	ft_print_string(t_print *tab, const char *str, int prec)
{
	int		n;
	char	*p;
	int		count;
	int		strlen;

	n = 0;
	count = 0;
	strlen = 0;
	p = (char *)str;
	strlen = ft_strlen(p);
	while (*p && prec)
	{
		if (++n > prec || (n > strlen))
			break ;
		if (ft_checkerror(tab, *p++) < 0)
			return (-1);
		count++;
	}
	while (count < tab->tlen && tab->dash)
	{
		if (ft_checkerror(tab, ' ') < 0)
			return (-1);
		count++;
	}
	return (count);
}
