#include "../../minishell.h"

bool	is_buff_valid_doll(char *str)
{
	int i;
	char starting_quote;
	char end_quote;

	i = 0;
	starting_quote = 0;
	end_quote = 0;

	while (str[i])
	{
		while (!is_any_quote(str[i]) && str[i])
		{
			if (str[i] == DOLL_ENV && !is_any_quote(str[i + 1]) && str[i + 1])
				return (true);
			i++;
		}
		if (is_any_quote(str[i]) && str[i])
		{
			starting_quote = str[i];
			i++;
			while (str[i] != starting_quote && str[i])
			{
				if (starting_quote == D_QUOTE && str[i] == DOLL_ENV && str[i + 1] != starting_quote)
					return (true);
				i++;
			}
		}
	}
	return (false);
}
int main()
{
	char *str = readline("MINISHELL$ ");


	if (is_buff_valid_doll(str))
		printf("Valid $ENV");
	else
		printf("WRONG INVALID $ENV");


	free(str);

	// ! wrong test
	/*
	"test1 test2   "test3 test4'test5 test6' "test7 test8"
	Supposed to give

	BUFF 0 "test1 test2   "test3
	BUFF 1 test4'test5 test6'
	BUFF 2 "test7 test8"
	
	*/

	


}