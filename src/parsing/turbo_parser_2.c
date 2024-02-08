/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/08 16:22:25 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_redir_in(t_pars **pars, char **splited, char **cleaned)
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strncmp(cleaned[i], RED_IN, 2) && !ft_strncmp(cleaned[i], splited[i], 2))
		{
			(*pars)->isRedirIn = true;
			break ;	
		} 
		else if (!ft_strncmp(cleaned[i], RED_IN_DELIM, 3) && !ft_strncmp(cleaned[i], splited[i], 3))
		{
			(*pars)->isRedirIn = true;
			break ;
		}
		i++;
	}
}
bool	is_token_command(char *splited, char *cleaned)
{
	
}
void	new_node_command(t_pars **pars, char *splited, char *cleaned)
{
	
}

bool	is_token_file(char *splited, char *cleaned)
{
	
}

void	new_node_file(t_pars **pars, char *splited, char *cleaned)
{
	
}

bool	is_token_operator(char *splited, char *cleaned)
{
	
	
}

void	new_node_operator(t_pars **pars, char *splited, char *cleaned)
{
	
}

void	pars_alloc(t_pars **pars, char **splited, char **cleaned)
{
	int i; // index of both split and cleaned

	i = 0;
	// ! step 1 : chase redir in operator, matching splited and cleaned
	search_redir_in(pars, splited, cleaned);
	// ! allocate the struct whatsoever
	while (cleaned[i]) // iterate over all tokens	
	{
		if (is_token_command(splited[i], cleaned[i]))
			new_node_command(pars, splited[i], cleaned[i]);
		else if (is_token_file(splited[i], cleaned[i]))
			new_node_file(pars, splited[i], cleaned[i]);
		else if (is_token_operator(splited[i], cleaned[i]))
			new_node_operator(pars, splited[i], cleaned[i]);
		// ! maybe another edge case ???
		i++;
	}
}
