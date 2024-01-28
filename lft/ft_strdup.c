/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:23:52 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/14 16:15:03 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *orig)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen((char *)orig) + 1);
	if (!dup)
		return (NULL);
	while (orig[i])
	{
		dup[i] = orig[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
