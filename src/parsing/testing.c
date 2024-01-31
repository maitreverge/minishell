#include "../../minishell.h"

// static char	*ft_strncpy(char *dest, char const *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n && src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

// static void	sub_check(char const *s, char c, size_t *i, size_t *start)
// {
// 	while (s[*i] == c)
// 		(*i)++;
// 	if (s[*i] != c && s[*i])
// 	{
// 		*start = *i;
// 		while (s[*i] != c && s[*i])
// 			(*i)++;
// 	}
// }

// static void	allocation(char **buffer, char const *s, char c, size_t len_s)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	start;

// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	if (!s)
// 		return ;
// 	while (s[i])
// 	{
// 		sub_check(s, c, &i, &start);
// 		if (j < len_s)
// 		{
// 			buffer[j] = ft_calloc(sizeof(char), (i - start + 1));
// 			if (!buffer[j])
// 				return ;
// 			ft_strncpy(buffer[j], &s[start], i - start);
// 			j++;
// 		}
// 		while (s[i] == c && s[i])
// 			i++;
// 	}
// }

// split the words, join them later
size_t	parsing_countwords(char *str)
{
	size_t i; // global index
	size_t result; // return value
	char start_quote;
	char end_quote;
	bool esc_whitespace;
	
	i = 0;
	result = 0;
	esc_whitespace = true;

	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;
		// skip whitespace chars
		while (is_whitespace(str[i]))
			i++;
		
		// ! first char is a quote
		if (is_any_quote(str[i]) && str[i])
		{
			// while (is_any_quote(str[i]) && str[i])
			while (is_any_quote(str[i]) && str[i])
			{
				start_quote = str[i];
				while(str[i] && start_quote != end_quote)
				{
					i++;
					if (str[i] == start_quote)
					{
						end_quote = start_quote;
						i++; // ! added
						break ;
					}
				}
				end_quote = 0;
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break;
				}
				while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break;
				}
			}
		}
		else if (!is_any_quote(str[i]) && str[i])
		{
			while (!is_any_quote(str[i]) && str[i])
			{
				while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
					i++;
				
				if (is_any_quote(str[i]) && str[i])
				{
					while (is_any_quote(str[i]) && str[i])
					{
						start_quote = str[i];
						while(str[i] && start_quote != end_quote)
						{
							i++;
							if (str[i] == start_quote)
							{
								end_quote = start_quote;
								break ;
							}
						}
						while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
							i++;
					}
				}
				result++;
			}
		}
	}



	return (result);
}

// char	**parsing_split(char const *s)
// {
// 	char	**buffer;
// 	size_t	len_s;

// 	len_s = parsing_countwords(s);
// 	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
// 	if (!buffer)
// 		return (NULL);
// 	allocation(buffer, s, c, len_s);
// 	return (buffer);
// }

int main()
{
	char *str = readline("MINISHELL$ ");
	int len_s = parsing_countwords(str);

	printf("There is %i words in the prompt\n", len_s);

}