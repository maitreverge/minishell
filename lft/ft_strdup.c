/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:23:52 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/15 13:40:25 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *orig)
{
	int		i;
	char	*dup;

	if (!orig)
		return (NULL);
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
