/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:41:47 by glambrig          #+#    #+#             */
/*   Updated: 2023/05/08 11:47:59 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	put_alpha(long long rem)
{
	if (rem == 10)
		return ('A');
	else if (rem == 11)
		return ('B');
	else if (rem == 12)
		return ('C');
	else if (rem == 13)
		return ('D');
	else if (rem == 14)
		return ('E');
	return ('F');
}

char	put_alpha_lowcase(long long rem)
{
	if (rem == 10)
		return ('a');
	else if (rem == 11)
		return ('b');
	else if (rem == 12)
		return ('c');
	else if (rem == 13)
		return ('d');
	else if (rem == 14)
		return ('e');
	return ('f');
}

/*for counting number of chars printed*/
int	counter_func(size_t n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

/*for %p*/
int	convert_dec_to_hex(unsigned long n, char mode, int *i)
{
	long long	rem;

	if (n >= 16)
		convert_dec_to_hex(n / 16, mode, i);
	rem = n % 16;
	if (rem >= 0 && rem <= 9)
		ft_putchar_fd(rem + '0', 1);
	else if ((rem >= 10 && rem <= 15) && mode == 'b')
		ft_putchar_fd(put_alpha(rem), 1);
	else if ((rem >= 10 && rem <= 15) && mode == 's')
		ft_putchar_fd(put_alpha_lowcase(rem), 1);
	(*i)++;
	return (*i);
}

/*for %xX*/
int	convert_dec_to_hex_x(unsigned int n, char mode, int *i)
{
	long long	rem;

	if (n >= 16)
		convert_dec_to_hex(n / 16, mode, i);
	rem = n % 16;
	if (rem >= 0 && rem <= 9)
		ft_putchar_fd(rem + '0', 1);
	else if ((rem >= 10 && rem <= 15) && mode == 'b')
		ft_putchar_fd(put_alpha(rem), 1);
	else if ((rem >= 10 && rem <= 15) && mode == 's')
		ft_putchar_fd(put_alpha_lowcase(rem), 1);
	(*i)++;
	return (*i);
}
