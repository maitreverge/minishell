/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:48:33 by flverge           #+#    #+#             */
/*   Updated: 2024/02/12 21:06:33 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	allocation(char **buffer, char const *s, char c)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	if (!s)
		return ;
	while (s[i] != c)
		i++;
	buffer[0] = ft_calloc(sizeof(char), (i - start + 1));
	if (!buffer[0])
		return ;
	ft_strncpy(buffer[0], s, i);
	i++;
	start = i;
	buffer[1] = ft_calloc(sizeof(char), (ft_strlen(&s[i]) + 1));
	if (!buffer[1])
		return ;
	ft_strncpy(buffer[1], &s[start], ft_strlen(&s[i]));
}

char	**ft_2_split(char const *s, char c)
{
	char	**buffer;

	buffer = (char **)ft_calloc(sizeof(char *), 3);
	if (!buffer)
		return (NULL);
	allocation(buffer, s, c);
	return (buffer);
}
