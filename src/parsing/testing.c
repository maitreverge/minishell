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
	char start_close;
	char end_close;
	
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