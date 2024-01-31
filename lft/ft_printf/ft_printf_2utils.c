/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:07:06 by glambrig          #+#    #+#             */
/*   Updated: 2023/05/08 11:48:16 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_s(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	put_u(unsigned int n, unsigned int counter)
{
	if (n >= 10)
		counter += put_u(n / 10, counter);
	ft_putchar_fd(n % 10 + '0', 1);
	counter++;
	return (counter);
}

int	put_d(int n)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2", 1);
		put_d(147483648);
		return (counter_func(147483647) + 2);
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', 1);
		ft_putnbr_fd(n, 1);
		return (counter_func(n) + 1);
	}
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_putnbr_fd(n, 1);
	return (counter_func(n));
}

int	put_small_x(long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		ft_putnbr_fd(0, 1);
		return (1);
	}
	else
		convert_dec_to_hex_x(n, 's', &i);
	return (i);
}

int	put_big_x(long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		ft_putnbr_fd(0, 1);
		return (1);
	}
	else
		convert_dec_to_hex_x(n, 'b', &i);
	return (i);
}
