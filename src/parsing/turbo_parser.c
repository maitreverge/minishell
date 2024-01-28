/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/01/28 18:18:58 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *realloc(char *old, char *new)
{
	char *new_str;

	new_str = ft_strjoin(old, new);
	
	free(old);
	free(new);
	
	return (new_str);
}

bool unclosed_quotes(char *str)
{
	size_t i;
	size_t s_quote;
	size_t d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE)
			d_quote++;
		else if (str[i] == S_QUOTE)
			s_quote++;
		i++;
	}
	if (s_quote != d_quote)
		return (true);
	return (false);
}

char **prompt_cleaning(char *prompt)
{
	char *result;
	int i;
	
	i = 0;
	while (prompt[i])
	{
		
		i++;
	}
	

	return (result);
}

void	turbo_parser(char *prompt, t_pars **pars, char **envp)
{
	char **cleaned_prompt;
	// ? 🤔 Does this function needs to be called during the nodes init 
	init_pars_struct(pars);

	// check la presence d'unclosed quotes.
	if (unclosed_quotes(prompt))
		exit (1);
		
	
	// ! STEP 1 : Take the whole string and "clean it"
	// ? maybe cleaning the prompt implies constantly reallocating a substring with the cleaned prompt 
	
	cleaned_prompt = prompt_cleaning(prompt); // custom split ?
	
	// ! STEP 2 : Create a new node each and everytime I met a Pipe, redirection, or something else
	// ! STEP 3 : Allocate substrings into substructures for commands and files
}