/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:25:22 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/15 15:13:06 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	if ((!dest || !src) && n == 0)
		return (0);
	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen((char *)src);
	if (n == 0 || n <= destlen)
		return (srclen + n);
	destlen = 0;
	while (dest[destlen] && destlen < n)
		destlen++;
	while (i < (n - destlen - 1) && src[i])
	{
		dest[i + destlen] = src[i];
		i++;
	}
	dest[i + destlen] = '\0';
	return (destlen + srclen);
}
