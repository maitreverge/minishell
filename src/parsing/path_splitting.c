/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:52 by flverge           #+#    #+#             */
/*   Updated: 2024/02/09 09:52:21 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*pipex_ft_strncpy(char *dest, char const *src, size_t n)
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

static void	p_sub_check(char const *s, char c, size_t *i, size_t *start)
{
	while (s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
	{
		*start = *i;
		while (s[*i] != c && s[*i])
			(*i)++;
	}
}

static void	p_alloc(char **buffer, char const *s, char c, size_t len_s)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	if (!s)
		return ;
	while (s[i])
	{
		p_sub_check(s, c, &i, &start);
		if (j < len_s)
		{
			buffer[j] = ft_calloc(sizeof(char), (i - start + 2));
			if (!buffer[j])
				return ;
			pipex_ft_strncpy(buffer[j], &s[start], i - start);
			ft_strlcat(buffer[j], "/", ft_strlen(buffer[j]) + 2);
			j++;
		}
		while (s[i] == c && s[i])
			i++;
	}
}

static size_t	ft_pipex_countwords(char const *str, char c)
{
	size_t	result;
	int		i;

	result = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			result++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (result);
}

char	**ft_pipex_split(char const *s, char c)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_pipex_countwords(s, c);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	p_alloc(buffer, s, c, len_s);
	return (buffer);
}