/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/02/04 15:36:21 by flverge          ###   ########.fr       */
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

/*

structure de George pour env

typedef struct s_env_list
{
	char *env_line;
	struct s_env_list *next;
}	t_env_list;

typedef struct s_all
{
	t_env_list	*env_lst;
	char		*readline_line;
	int			last_exit_status;
}	t_all;

*/

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

char **clean_prompt(char **buff, int len)
{
	t_utils *u;

	utils_init_struct(&u, len);

	while (buff[u->i])
	{
		u->j = 0;
		u->real_len = 0;
		while (is_buff_valid_doll(buff[u->i]))
		{
			// custom_parsing;
			u->i++;
		}
		
			
		// ! STEP 1 : enterring in each buffer, calculatting the correct amount of letter to allocate
		while (buff[u->i][u->j])
		{
			while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j])
			{
				u->j++;
				u->real_len++;
			}
			if(is_any_quote(buff[u->i][u->j]))
			{
				u->starting_quote = buff[u->i][u->j];
				u->j++; // skips the quote
				while (buff[u->i][u->j] && buff[u->i][u->j] != u->starting_quote)
				{
					u->j++;
					u->real_len++;
				}
				u->j++;
			}
		}
		u->j = 0;
		u->k = 0;
		// ! STEP 2 : allocating the buffer result with calloc
		
		u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
		if (!u->result[u->i])
			exit -1; // la maxi security tavu
		
		// ! STEP 3 : copying the "cleaned" version of each input
		while (buff[u->i][u->j])
		{
			while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j])
			{
				u->result[u->i][u->k] = buff[u->i][u->j];
				u->j++;
				u->k++;
			}
			if(is_any_quote(buff[u->i][u->j]))
			{
				u->starting_quote = buff[u->i][u->j];
				u->j++; // skips the quote
				while (buff[u->i][u->j] && buff[u->i][u->j] != u->starting_quote)
				{
					u->result[u->i][u->k] = buff[u->i][u->j];
					u->j++;
					u->k++;
				}
				u->j++;
			}
		}
		u->i++;
	}
	return (u->result);
}

void	turbo_parser(char *prompt, t_pars **pars, char **envp)
{
	// ! brancher la strcuture all de G pour brancher 
	int	len_splited_prompt;
	char **splited_prompt;
	char **cleaned_prompt;
	
	// ? 🤔 Does this function needs to be called during the nodes init 
	// init_pars_struct(pars);

	len_splited_prompt = parsing_countwords(prompt);

	// check la presence d'unclosed quotes.
	if (unclosed_quotes(prompt))
		exit (1); // ? need freeing 
		
	// ! STEP 1 : Take the whole prompt and split it
	splited_prompt = parsing_split(prompt);
	cleaned_prompt = clean_prompt(splited_prompt, len_splited_prompt);
	
	// ! printing the whole shit
	// for (int i = 0; i <= len_splited_prompt; i++)
	// {
	// 	printf("Cleaned Buffer #%i = %s\n", i+1, cleaned_prompt[i]);
	// }

	free_split(splited_prompt);
	
	
	// ! STEP 2 : Create a new node each and everytime I met a Pipe, redirection, or something else
	
	// ! STEP 3 : Allocate substrings into substructures for commands and files
}