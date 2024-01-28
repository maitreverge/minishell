/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:51:16 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/16 16:01:51 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Will always return at least 1 [digit], adds 1 for minus sign*/
static size_t	counter_func(int n)
{
	int	counter;

	counter = 0;
	if (n < 0)
		counter = 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static char	*is_zero(int n, char *str)
{
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	return (str);
}

char	*ft_itoa(int nb)
{
	char		*str;
	size_t		len;
	long long	n;

	n = nb;
	len = counter_func(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	is_zero(n, str);
	while (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n > 0)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}
