/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:43:54 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:35:52 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	alloc_part_1(t_alloc *c, int *i, t_pars **pars, t_alloc **u_alloc)
{
	if (is_token_pipe(c->splitted_prompt[(*i)], c->cleaned_prompt[(*i)]))
	{
		lstfirst(*pars)->masterkill = true;
		ft_putendl_fd("First Token is a Pipe\n", 2);
		return (true);
	}
	else if (is_token_opr(c->splitted_prompt[(*i)], c->cleaned_prompt[(*i)]))
		new_node_operator(pars, c->cleaned_prompt[(*i)]);
	else if (!is_token_opr(c->splitted_prompt[(*i)], c->cleaned_prompt[(*i)]))
		new_node_command(pars, u_alloc, i);
	return (false);
}

bool	alloc_part_2(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->masterkill = true;
		ft_putendl_fd("Token following a command isn't a operator\n", 2);
		return (true);
	}
	return (false);
}

bool	alloc_part_3(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_pipe(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)])
		|| is_token_redir_out(cur->splitted_prompt[(*i)],
			cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->masterkill = true;
		ft_putendl_fd("Token following a file isn't a PIPE or RED_OUT\n", 2);
		return (true);
	}
	return (false);
}

bool	alloc_part_4(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_pipe(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)])
		|| is_token_redir_out(cur->splitted_prompt[(*i)],
			cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->masterkill = true;
		ft_putendl_fd("Token following a HERE_DOC isn't a PIPE / RED_OUT\n", 2);
		return (true);
	}
	return (false);
}

bool	alloc_part_5(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	if (is_last_node_pipe(pars)
		&& !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_command(pars, u_alloc, i);
	else if (is_last_node_redir(pars)
		&& !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_file(pars, cur->cleaned_prompt[(*i)]);
	else if (is_last_node_r_in_delim(pars)
		&& !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_here_doc(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->masterkill = true;
		ft_putendl_fd("Two consecutives operators\n", 2);
		return (true);
	}
	return (false);
}
