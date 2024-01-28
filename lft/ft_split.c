/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:08:24 by glambrig          #+#    #+#             */
/*   Updated: 2023/02/19 15:33:28 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *str, char c)
{
	size_t	count;
	int		i;
	int		testnext;

	i = 0;
	count = 0;
	testnext = 0;
	while (str[i])
	{
		if (str[i] != c && testnext == 0)
		{
			count++;
			testnext = 1;
		}
		else if (str[i] == c)
			testnext = 0;
		i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char		*dest;
	size_t		i;
	size_t		k;

	k = 0;
	i = 0;
	while (s1[k] && k < n)
		k++;
	dest = (char *)malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (s1[i] && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*J and Pos keep track of the start and end of the substrings respectively*/

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		pos = i;
		while (s[i] && s[i] != c)
			i++;
		if (pos != i)
		{
			tab[j] = ft_strndup(s + pos, i - pos);
			j++;
		}
		if (s[i])
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
