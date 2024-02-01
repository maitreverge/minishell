/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:57:43 by flverge           #+#    #+#             */
/*   Updated: 2024/02/01 13:10:43 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return true;
	return false;
}

bool	is_any_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (true);
	return (false);
}

void	free_split(char **to_free)
{
	char	**current;
	int		i;

	i = 0;
	current = to_free;
	while (current[i])
	{
		free(current[i]);
		i++;
	}
	free(to_free);
}

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
