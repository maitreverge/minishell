/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:36:46 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 19:15:52 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strncpy(char *dest, char const *src, size_t n)
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

static void	sub_check(char const *s, char c, size_t *i, size_t *start)
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

static void	allocation(char **buffer, char const *s, char c, size_t len_s)
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
		sub_check(s, c, &i, &start);
		if (j < len_s)
		{
			buffer[j] = ft_calloc(sizeof(char), (i - start + 1));
			if (!buffer[j])
				return ;
			ft_strncpy(buffer[j], &s[start], i - start);
			j++;
		}
		while (s[i] == c && s[i])
			i++;
	}
}

static size_t	ft_countwords(char const *str, char c)
{
	size_t	result;
	int		i;
	int s_quote;
	int d_quote;


	result = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		s_quote = 0;
		d_quote = 0;
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			result++;
			while (str[i] && str[i] != c && ((s_quote % 2) || (d_quote % 2)))
			{
				if (str[i] == S_QUOTE)
					s_quote++;
				else if (str[i] == D_QUOTE)
					d_quote++;
				i++;
			}
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_countwords(s, c);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	allocation(buffer, s, c, len_s);
	return (buffer);
}

/*
edge case
           "ec'h' o"    bonjour
		   '  '   '   'echo'   

*/
