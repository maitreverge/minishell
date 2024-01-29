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


bool unclosed_quotes(char *str) // e"c'h"o ==> ec'ho, is then technically a valid argument
{
	size_t i;
	char starting_quote;
	char closing_quote;

	i = 0;
	while (str[i])
	{
		starting_quote = 0;
		closing_quote = 0;

		// ! Step one, run accross non quote chars
		while (str[i] != D_QUOTE && str[i] != S_QUOTE && str[i])
			i++;
		
		if (str[i] == D_QUOTE) // if the current char is a double quote
		{
			starting_quote = str[i];
			i++;
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
		else if (str[i] == S_QUOTE) // if the current char is a single quote
		{
			starting_quote = str[i];
			i++;
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
	if (starting_quote != closing_quote)
		return (true);
	return (false);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *str;

	str = readline("MINISHELL $ ");

	printf("str = %s\n", str);
	if (unclosed_quotes(str))
		printf("result of unclosed quote = TRUE");
	else
		printf("result of unclosed quote = FALSE");
		

	// add_history(str);

	// free(str);

}