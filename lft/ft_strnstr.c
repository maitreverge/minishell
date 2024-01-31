/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:26:53 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/15 15:14:26 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if ((!big || !small) && len == 0)
		return (NULL);
	if (!small[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == small[j] && i + j < len)
		{
			j++;
			if (small[j] == '\0')
				return ((char *)big + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
