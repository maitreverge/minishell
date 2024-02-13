/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:20 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 10:59:41 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_token_operator(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, RED_IN))
			return (true);
		else if (!ft_strcmp(cleaned, RED_IN_DELIM))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT_APP))
			return (true);
		else if (!ft_strcmp(cleaned, PIPE))
			return (true);
	}
	return (false);
}

bool	is_token_redir_delim(char *cleaned)
{
	if (!ft_strcmp(cleaned, RED_IN_DELIM))
		return (true);
	return (false);
}

bool	is_token_pipe(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, PIPE))
			return (true);
	}
	return (false);
}

bool	is_token_redir_out(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, RED_OUT))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT_APP))
			return (true);
	}
	return (false);
}

bool	is_last_node_operator(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->isOperator)
		return (true);
	return (false);
}
