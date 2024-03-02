/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:55:59 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:16:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_last_node_redir(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->operator)
	{
		if (last->operator->redir_in || last->operator->redir_out
			|| last->operator->redir_out_app)
			return (true);
	}
	return (false);
}

bool	is_last_node_r_in_delim(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->operator)
	{
		if (last->operator->redir_in_delim)
			return (true);
	}
	return (false);
}

bool	is_last_node_here_doc(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->is_here_doc)
		return (true);
	return (false);
}

bool	is_last_node_cmd(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->is_command)
		return (true);
	return (false);
}

bool	is_last_node_file(t_pars **pars)
{
	t_pars	*last;

	last = lstlast(*pars);
	if (last->is_file)
		return (true);
	return (false);
}
