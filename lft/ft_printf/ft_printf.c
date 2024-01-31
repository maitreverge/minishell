/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:39:57 by glambrig          #+#    #+#             */
/*   Updated: 2023/05/08 11:48:04 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*clear && make re && valgrind --track-origins=yes --leak-check=full ./a.out*/

/*+2 for the "0x" is added in printf function itself, not here.*/
int	put_p(void *num, char mode)
{
	int	len;

	len = 0;
	if (num == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		len = convert_dec_to_hex((unsigned long)num, mode, &len);
	}
	return (len + 2);
}

int	put_c(int n)
{
	ft_putchar_fd(n, 1);
	return (1);
}

int	check_char(const char *str, int i, va_list list)
{
	if (str[i] == 'c')
		return (put_c(va_arg(list, int)));
	else if (str[i] == 's')
		return (put_s(va_arg(list, char *)));
	else if (str[i] == 'p')
		return (put_p(va_arg(list, void *), 's'));
	else if (str[i] == 'd' || str[i] == 'i')
		return (put_d(va_arg(list, int)));
	else if (str[i] == 'u')
		return (put_u(va_arg(list, unsigned int), 0));
	else if (str[i] == 'x')
		return (put_small_x(va_arg(list, long long int)));
	else if (str[i] == 'X')
		return (put_big_x(va_arg(list, long long int)));
	else if (str[i] == '%')
	{	
		write(1, "%", 1);
		return (1);
	}
	else
	{
		ft_putstr_fd("Error: invalid format specifier (cspdiuxX%).", 1);
		return (44);
	}
}

/*check_char checks the next char for format specifier*/
int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	list;

	i = 0;
	count = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += check_char(str, i + 1, list);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			count++;
			i++;
		}
	}
	va_end(list);
	return (count);
}
