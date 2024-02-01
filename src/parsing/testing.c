#include "../../minishell.h"

static void	allocation(char **buffer, char const *str, size_t len_s)
{
	size_t	i; // global index
	size_t	j; // index d'allocation de buffer char **
	size_t	start; // little checkpoint for remembering reversed allocation starting point
	char start_quote;
	char end_quote;

	i = 0;
	j = 0;
	start = 0;
	if (!str)
		return ;
	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;

		// ! skip whitespaces
		while (is_whitespace(str[i]) && str[i])
			i++;

		// ! skip to the next following word
		// need to kickstart start = i in each case
		if (is_any_quote(str[i]) && str[i])
		{
			start = i; // indexing checkpoint
			while (is_any_quote(str[i]) && str[i])
			{
				start_quote = str[i];
				while(str[i] && start_quote != end_quote)
				{
					i++;
					if (str[i] == start_quote)
					{
						end_quote = start_quote;
						i++;
						break ;
					}
				}
				end_quote = 0;
				if (is_whitespace(str[i]) || !str[i])
					break;
				while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
					i++;
				if (is_whitespace(str[i]) || !str[i])
					break;
			}
		}
		else if (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
		{
			start = i; // indexing checkpoint
			while (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i]))
			{
				while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
					i++;
				
				if (is_whitespace(str[i]) || !str[i])
					break;
				
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
								i++;
								break ;
							}
						}
						end_quote = 0;
						if (is_whitespace(str[i]) || !str[i])
							break;
						
						while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
							i++;
						if (is_whitespace(str[i]) || !str[i])
							break;
					}
				}
			}
		}

		// ! allocation function alamano
		if (j < len_s)
		{
			buffer[j] = ft_calloc(sizeof(char), (i - start + 1));
			if (!buffer[j])
				return ;
			ft_strncpy(buffer[j], &str[start], i - start);
			j++;
		}
	}
}

size_t	parsing_countwords(char *str)
{
	size_t i; // global index
	size_t result; // return value
	char start_quote;
	char end_quote;
	
	i = 0;
	result = 0;

	while (str[i])
	{
		start_quote = 0;
		end_quote = 0;
		while (is_whitespace(str[i]) && str[i])
			i++;
		
		// ! first char is a quote
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
						i++;
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
		else if (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i])) // MAYBE ADD WHITE
		{
			while (!is_any_quote(str[i]) && str[i] && !is_whitespace(str[i])) // MAYBE ADD WHITE
			{
				while(str[i] && !is_whitespace(str[i]) && !is_any_quote(str[i]))
					i++;
				
				if (is_whitespace(str[i]) || !str[i])
				{
					result++;
					break;
				}
				
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
								i++; // ! added last minute
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
			}
		}
	}
	return (result);
}

char	**parsing_split(char *s)
{
	char	**buffer;
	size_t	len_s;

	len_s = parsing_countwords(s);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	allocation(buffer, s, len_s);
	return (buffer);
}

int main()
{
	char **buffer;
	char *str = readline("MINISHELL$ ");


	int len_s = parsing_countwords(str);
	printf("There is %i words in the prompt\n", len_s);

	buffer = parsing_split(str);

	for (int i = 0; i <= len_s; i++)
	{
		printf("Buffer #%i = %s\n", i+1, buffer[i]);
	}


	free_split(buffer);

	// ! wrong test
	/*
	"test1 test2   "test3 test4'test5 test6' "test7 test8"
	Supposed to give

	BUFF 0 "test1 test2   "test3
	BUFF 1 test4'test5 test6'
	BUFF 2 "test7 test8"
	
	*/

	


}