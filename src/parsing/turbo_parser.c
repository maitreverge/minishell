/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/02/09 09:29:40 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// This function needs to check 
bool unclosed_quotes(char *str) // e"c'h"o ==> ec'ho, is then technically a valid argument
{
	size_t i;
	char starting_quote;
	char closing_quote;

	i = 0;
	if (!str)
		return true;
	while (str[i]) // invalid read size 
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
		if (str[i])
			i++;
	}
	if (starting_quote != closing_quote)
		return (true);
	return (false);
}


bool	is_buff_valid_doll(char *str)
{
	int i;
	char starting_quote;
	char end_quote;

	i = 0;
	starting_quote = 0;
	end_quote = 0;

	if (!str)
		return false;

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

void	calculate_len_doll(char *buff, t_utils **u, t_env_list **s_env, t_pars **pars)
{
	t_env_list *current_env;
	int i;
	char *temp_str;

	current_env = *s_env;
	i = 0;
	int start = 0;

	while (!is_any_quote(buff[i]) && buff[i] != DOLL_ENV && !is_whitespace(buff[i]) && buff[i])
		i++;
	temp_str = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!temp_str)
		exit(-1); // failed malloc
	ft_strncpy(temp_str, &buff[start], i);
	
	while (current_env)
	{
		if (!ft_strcmp(temp_str, "?")) // ! edge case for $? 
		{
			(*u)->real_len += int_len((*pars)->last_exit_status); // ! add to real len the len of s_env->value
			break ;
		}
		else if (!ft_strcmp(temp_str, current_env->key))
		{
			(*u)->real_len += ft_strlen(current_env->value); // ! add to real len the len of s_env->value
			break ;
		}
		current_env = current_env->next;
	}
	
	(*u)->j += i; // move the curser
	free(temp_str);
	
}

void	copying_doll(char *buff, t_utils **utils, t_env_list **s_env, t_pars **pars)
{
	t_env_list *current_env;
	t_utils *u;
	int i;
	char *temp_str;
	char *nbr;

	current_env = *s_env;
	u = *utils;
	i = 0;
	int start = 0;

	while (!is_any_quote(buff[i]) && buff[i] != DOLL_ENV && !is_whitespace(buff[i]) && buff[i])
		i++;
	temp_str = (char *)ft_calloc(sizeof(char), i + 1); // !! fix calloc multiple arguments
	if (!temp_str)
		exit(-1); // failed malloc
	ft_strncpy(temp_str, &buff[start], i);
	
	while (current_env)
	{
		if (!ft_strcmp(temp_str, "?")) // ! edge case for $? 
		{
			nbr = ft_itoa((*pars)->last_exit_status);
			while (nbr[start])
			{
				u->result[u->i][u->k] = nbr[start];
				u->k++;
				start++;
			}
			free(nbr);
			break;
		}
		else if (!ft_strcmp(temp_str, current_env->key))
		{
			while (current_env->value[start])
			{
				u->result[u->i][u->k] = current_env->value[start];
				u->k++;
				start++;
			}
			break ;
		}
		current_env = current_env->next;
	}
	u->j += i; // move the curser
	free(temp_str);
	
}

void	parsing_doll_var(t_utils **utils, char *buff, t_env_list **s_env, t_pars **pars)
{
	t_utils *u;
	char *result;
	char *temp_doll;
	bool expansion;

	u = *utils;
	expansion = true;

	
	// ! STEP 1 : enterring in each buffer, calculatting the correct amount of letter to allocate
	while (buff[u->j])
	{
		while (!is_any_quote(buff[u->j]) && buff[u->j])
		{
			expansion = true;
			// ! STEP 1.1 : stop at the first encoutered dollar sign 
			if (buff[u->j] == DOLL_ENV && expansion)
			{
				u->j++;
				calculate_len_doll(&buff[u->j], &u, s_env, pars);
			}
			else
			{
				u->j++;
				u->real_len++;
			}
		}
		if(is_any_quote(buff[u->j]))
		{
			u->starting_quote = buff[u->j];
			u->j++; // skips the quote
			if (u->starting_quote == S_QUOTE)
				expansion = false;
			while (buff[u->j] && buff[u->j] != u->starting_quote)
			{
				if (buff[u->j] == DOLL_ENV && expansion)
				{
					u->j++;
					calculate_len_doll(&buff[u->j], &u, s_env, pars);
				}
				else
				{
					u->j++;
					u->real_len++;
				}
			}
			u->j++;
		}
	}
	// ? Does the current dollar sign meet the expension criterias ?
	// ! NO ==> Skip the whole $block until the next $ sign, quote or space if not inside a quote
	// * YES 
	// ? Does the key exists in s_env ?
	// * NO
	// ! NO ==> Skip the whole $block until the next $ sign, quote or space if not inside a quote
	// * YES ==> assign the `value` into a temp char*, count the whole value strlen, add it to real_len, skip i  

	// ! STEP 2 : allocating the buffer result with calloc


	u->j = 0;
	u->k = 0;
	u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
	if (!u->result[u->i])
		exit -1; // la maxi security tavu

	// ! STEP 3 : copying the "cleaned" version of each input

	while (buff[u->j])
	{
		while (!is_any_quote(buff[u->j]) && buff[u->j])
		{
			expansion = true;
			if (buff[u->j] == DOLL_ENV && expansion)
			{
				u->j++;
				copying_doll(&buff[u->j], &u, s_env, pars);
			}
			else
			{
				u->result[u->i][u->k] = buff[u->j];
				u->j++;
				u->k++;
			}

		}
		if(is_any_quote(buff[u->j]))
		{
			u->starting_quote = buff[u->j];
			u->j++; // skips the quote
			if (u->starting_quote == S_QUOTE)
				expansion = false;
			while (buff[u->j] && buff[u->j] != u->starting_quote)
			{
				if (buff[u->j] == DOLL_ENV && expansion)
				{
					u->j++;
					copying_doll(&buff[u->j], &u, s_env, pars);
				}
				else
				{
					u->result[u->i][u->k] = buff[u->j];
					u->j++;
					u->k++;
				}
			}
			u->j++;
		}
	}
}

char **ft_clean_prompt(char **buff, t_utils **utils, t_env_list **s_env, t_pars **pars)
{
	t_utils *u;

	u = *utils;
	
	while (buff[u->i])
	{
		u->j = 0;
		u->real_len = 0;
		// special parsing for doll env
		while (is_buff_valid_doll(buff[u->i]))
		{
			parsing_doll_var(&u, buff[u->i], s_env, pars); // ! sub function for special parsing the doll (envie de crever MAXIMALE, plaisir ABSENT uWu)
			u->i++;
		}
		if (!buff[u->i])
			break ;
		u->j = 0;
		u->real_len = 0;
		
			
		// ! STEP 1 : enterring in each buffer, calculatting the correct amount of letter to allocate
		// while (buff[u->i])
		while (buff[u->i][u->j] != 0)
		{
			while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j] != 0)
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
		// while (buff[u->i][u->j])
		// while (buff[u->i]) ///////////////
		while (buff[u->i][u->j] != 0)
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
		u->i++; // ! changing buffer
	}
	return (u->result); // return value of structure
}

void	turbo_parser(char *prompt, t_pars **pars, t_env_list **s_env, t_utils **s_utils)
{
	t_utils *u;
	int	len_splited_prompt;
	char **splited_prompt;
	char **cleaned_prompt;
	char **paths;


	
	u = *s_utils;

	len_splited_prompt = parsing_countwords(prompt);

	if (unclosed_quotes(prompt))
	{
		ft_putendl_fd("Error : Unclosed quote detected", 2);
		ft_putendl_fd("Please enter a valid prompt", 2);
		// CTRL - C SIGNAL
		// ! free struff ?
	}

	u = utils_init_struct(len_splited_prompt);
		
	splited_prompt = parsing_split(prompt);

	for (int i = 0; splited_prompt[i]; i++)
	{
		printf("Splitted Buffer #%i = %s\n", i+1, splited_prompt[i]);
	}
	printf("\n\n");

	
	cleaned_prompt = ft_clean_prompt(splited_prompt, &u, s_env, pars);
	
	for (int i = 0; cleaned_prompt[i]; i++)
	{
		printf("Cleaned Buffer #%i = %s\n", i+1, cleaned_prompt[i]);
	}

	// ! STEP 2 : Create a new node each and everytime I met a Pipe, redirection, or something else
	
	paths = extract_paths(s_env);
	pars_alloc(pars, splited_prompt, cleaned_prompt);
	// ! STEP 3 : Allocate substrings into substructures for commands and files

	
	free_s_utils(&u);
	free_split(splited_prompt);
	free_split(paths);
	
	
	
}