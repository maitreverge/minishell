/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:42:07 by glambrig          #+#    #+#             */
/*   Updated: 2023/03/20 14:41:11 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dup;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start >= (size_t)ft_strlen((char *)s))
		return (ft_strdup(""));
	i = 0;
	if (len > slen - start)
		len = slen - start;
	dup = malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[start] && i < len)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}
