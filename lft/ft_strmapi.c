/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:44:56 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/16 15:40:10 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*fptr)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = fptr(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
