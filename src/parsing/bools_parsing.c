/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:20 by flverge           #+#    #+#             */
/*   Updated: 2024/02/12 18:21:37 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_token_operator(char *splited, char *cleaned)
{
	// ! checks if there is a operator intead of an operator within quotes
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

bool is_token_redir_delim(char *cleaned)
{
	if (!ft_strcmp(cleaned, RED_IN_DELIM))
		return true;
	return false;
	
}

bool is_token_pipe(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, PIPE))
			return (true);
	}
	return (false);
}

bool is_token_redir_out(char *splited, char *cleaned)
{
	if (!ft_strcmp(splited, cleaned))
	{
		if (!ft_strcmp(cleaned, PIPE))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT))
			return (true);
		else if (!ft_strcmp(cleaned, RED_OUT_APP))
			return (true);
	}
	return (false);
}

bool is_last_node_operator(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isOperator)
		return (true);
	return (false);
}

bool is_last_node_pipe(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator)
	{
		if (last->operator->pipe)
			return (true);
	}
	return (false);
}

// ! checks if > >> and <
bool is_last_node_redir(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator)
	{
		if (last->operator->redir_in || last->operator->redir_out || last->operator->redir_out_app)
			return (true);
	}
	return (false);
}

bool is_last_node_r_in_delim(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->operator)
	{
		if (last->operator->redir_in_delim)
			return (true);
	}
	return (false);
}

bool is_last_node_here_doc(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isHereDoc)
		return (true);
	return (false);
}

bool is_last_node_cmd(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isCommand)
		return (true);
	return (false);
}

bool is_last_node_file(t_pars **pars)
{
	t_pars *last;

	last = lstlast(*pars);

	if (last->isFile)
		return (true);
	return (false);
}

