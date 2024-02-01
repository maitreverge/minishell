/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/02/01 14:01:58 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char *realloc(char *old, char *new)
// {
// 	char *new_str;

// 	new_str = ft_strjoin(old, new);
	
// 	free(old);
// 	free(new);
	
// 	return (new_str);
// }

// This function needs to check 
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
		
		if (str[i] == D_QUOTE || str[i] == S_QUOTE) // if the current char is a double quote
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

char **clean_prompt(char **buff, int len)
{
	char **result;
	result = (char **)malloc(sizeof(char *) * len + 1)
	if (!result)
		exit(-1); // ! maybe freeing shit right here
	
	// ! STEP 1 : enterring in each buffer, calculatting the correct amount of letter to allocate

	
	// ! STEP 2 : allocating the buffer result with calloc

	
	// ! STEP 3 : copying the "cleaned" version of each input

	
	

	return (result);
}

void	turbo_parser(char *prompt, t_pars **pars, char **envp)
{
	int	len_splited_prompt;
	char **splited_prompt;
	char **cleaned_prompt;
	// ? 🤔 Does this function needs to be called during the nodes init 
	init_pars_struct(pars);

	len_splited_prompt = parsing_countwords(prompt);

	// check la presence d'unclosed quotes.
	if (unclosed_quotes(prompt))
		exit (1); // ? need freeing 
		
	// ! STEP 1 : Take the whole prompt and split it
	splited_prompt = parsing_split(prompt);
	cleaned_prompt = clean_prompt(splited_prompt, len_splited_prompt);
	free_split(splited_prompt);
	
	
	// ! STEP 2 : Create a new node each and everytime I met a Pipe, redirection, or something else
	
	// ! STEP 3 : Allocate substrings into substructures for commands and files
}