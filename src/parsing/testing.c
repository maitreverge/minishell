# define S_QUOTE '\'' // backslack for making it a char
# define D_QUOTE '\"'
# define PIPE '|'
# define RED_IN '<'
# define RED_IN_DELIM "<<"
# define RED_OUT '>'
# define RED_OUT_APP ">>"
# define DOLL_ENV '$'
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


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

// split the words, join them later
static size_t	parsing_countwords(char const *str, char c)
{
	size_t	result;
	int		i;
	char starting_quote;
	char closing_quote;

	i = 0;
	while (str[i])
	{
		starting_quote = 0;
		closing_quote = 0;

		// skip whitespaces
		

		while (str[i] != D_QUOTE && str[i] != S_QUOTE && str[i])
			i++;
		
		if (str[i] == D_QUOTE || str[i] == S_QUOTE) // if the current char is a double quote
		{
			starting_quote = str[i];
			i++;
			result++;
			while (str[i] && starting_quote != closing_quote)
			{
				if (str[i] == starting_quote)
				{
					closing_quote = starting_quote;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (result);
}

char	**parsing_split(char const *s, char c)
{
	char	**buffer;
	size_t	len_s;

	len_s = parsing_countwords(s, c);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	allocation(buffer, s, c, len_s);
	return (buffer);
}

int main()
{
	

}