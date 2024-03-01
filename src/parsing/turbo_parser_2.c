/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 17:09:07 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	last_checker(t_pars **pars)
{
	t_pars *last;
	t_pars *first_node;

	first_node = *pars;
	last = lstlast(*pars);

	if (last->isOperator)
	{
		first_node->MasterKill = true;
		ft_putendl_fd("Last token is an operator\n", 2);
	}
	else if (first_node->isOperator && first_node->operator->redir_in && first_node->next->isFile && !first_node->next->fl->file_exist)
	{
		first_node->MasterKill = true;
		ft_putendl_fd("File does not exists\n", 2);
	}
}

static bool part_1(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	if (is_token_pipe(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
	{
		lstfirst(*pars)->MasterKill = true;
		ft_putendl_fd("First Token is a Pipe\n", 2);
		return (true);
	}
	else if (is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else if (!is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_command(pars, u_alloc, i);
	return (false);
}

static bool part_2(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->MasterKill = true;
		ft_putendl_fd("Token following a command isn't a operator\n", 2);
		return (true);
	}
	return (false);
}

static bool part_3(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_pipe(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]) || is_token_redir_out(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->MasterKill = true;
		ft_putendl_fd("Token following a file isn't a PIPE or RED_OUT operator\n", 2);
		return (true);
	}
	return (false);
}

static bool part_4(t_alloc *cur, int *i, t_pars **pars)
{
	if (is_token_pipe(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)])
		|| is_token_redir_out(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_operator(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->MasterKill = true;
		ft_putendl_fd("Token following a HERE_DOC isn't a PIPE or RED_OUT operator\n", 2);
		return (true);
	}
	return (false);
}

static bool part_5(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	if (is_last_node_pipe(pars) && !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_command(pars, u_alloc, i);
	else if (is_last_node_redir(pars) && !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_file(pars, cur->cleaned_prompt[(*i)]);
	else if (is_last_node_r_in_delim(pars) && !is_token_opr(cur->splitted_prompt[(*i)], cur->cleaned_prompt[(*i)]))
		new_node_here_doc(pars, cur->cleaned_prompt[(*i)]);
	else
	{
		lstfirst(*pars)->MasterKill = true;
		ft_putendl_fd("Two consecutives operators\n", 2);
		return (true);
	}
	return (false);
}

bool	big_norm(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	t_pars	*last_p_node;

	last_p_node = lstlast(*pars);
	if (!last_p_node->prev) // gestion du premier noeud
	{
		if (part_1(cur, i, pars, u_alloc))
			return (true);
		// if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// {
		// 	lstfirst(*pars)->MasterKill = true;
		// 	ft_putendl_fd("First Token is a Pipe\n", 2);
		// 	break ;
		// }
		// else if (is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_operator(pars, cur->cleaned_prompt[i]);
		// else if (!is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_command(pars, u_alloc, &i);
	}
	else if ((is_last_node_cmd(pars)))
	{
		if (part_2(cur, i, pars))
			return (true);
		// if (is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_operator(pars, cur->cleaned_prompt[i]);
		// else
		// {
		// 	lstfirst(*pars)->MasterKill = true;
		// 	ft_putendl_fd("Token following a command isn't a operator\n", 2);
		// 	break ;
		// }
	}
	else if (is_last_node_file(pars))
	{
		if (part_3(cur, i, pars))
			return (true);
		// if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]) || is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_operator(pars, cur->cleaned_prompt[i]);
		// else
		// {
		// 	lstfirst(*pars)->MasterKill = true;
		// 	ft_putendl_fd("Token following a file isn't a PIPE or RED_OUT operator\n", 2);
		// 	break ;
		// }
	}
	else if (is_last_node_here_doc(pars))
	{
		if (part_4(cur, i, pars))
			return (true);
		// if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i])
		// 	|| is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_operator(pars, cur->cleaned_prompt[i]);
		// else
		// {
		// 	lstfirst(*pars)->MasterKill = true;
		// 	ft_putendl_fd("Token following a HERE_DOC isn't a PIPE or RED_OUT operator\n", 2);
		// 	break ;
		// }
	}
	else if (is_last_node_operator(pars))
	{
		if (part_5(cur, i, pars, u_alloc))
			return (true);
		// if (is_last_node_pipe(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_command(pars, u_alloc, &i);
		// else if (is_last_node_redir(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_file(pars, cur->cleaned_prompt[i]);
		// else if (is_last_node_r_in_delim(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	new_node_here_doc(pars, cur->cleaned_prompt[i]);
		// else
		// {
		// 	lstfirst(*pars)->MasterKill = true;
		// 	ft_putendl_fd("Two consecutives operators\n", 2);
		// 	break ;
		// }
	}
	return (false);
}

void	pars_alloc(t_pars **pars, t_alloc **u_alloc)
{
	t_alloc	*cur;
	// t_pars	*last_p_node;
	int		i;

	cur = *u_alloc;
	i = 0;
	search_redir_in(pars, cur->splitted_prompt, cur->cleaned_prompt);
	while (cur->cleaned_prompt[i])
	{
		if (big_norm(cur, &i, pars, u_alloc))
			break ;
		// !!!!!!!!!!!!!!!
		// !!!!!!!!!!!!!!!
		// last_p_node = lstlast(*pars);
		// if (!last_p_node->prev) // gestion du premier noeud
		// {
		// 	if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 	{
		// 		lstfirst(*pars)->MasterKill = true;
		// 		ft_putendl_fd("First Token is a Pipe\n", 2);
		// 		break ;
		// 	}
		// 	else if (is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_operator(pars, cur->cleaned_prompt[i]);
		// 	else if (!is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_command(pars, u_alloc, &i);
		// }
		// else if ((is_last_node_cmd(pars)))
		// {
		// 	if (is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_operator(pars, cur->cleaned_prompt[i]);
		// 	else
		// 	{
		// 		lstfirst(*pars)->MasterKill = true;
		// 		ft_putendl_fd("Token following a command isn't a operator\n", 2);
		// 		break ;
		// 	}
		// }
		// else if (is_last_node_file(pars))
		// {
		// 	if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i]) || is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_operator(pars, cur->cleaned_prompt[i]);
		// 	else
		// 	{
		// 		lstfirst(*pars)->MasterKill = true;
		// 		ft_putendl_fd("Token following a file isn't a PIPE or RED_OUT operator\n", 2);
		// 		break ;
		// 	}
		// }
		// else if (is_last_node_here_doc(pars))
		// {
		// 	if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i])
		// 		|| is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_operator(pars, cur->cleaned_prompt[i]);
		// 	else
		// 	{
		// 		lstfirst(*pars)->MasterKill = true;
		// 		ft_putendl_fd("Token following a HERE_DOC isn't a PIPE or RED_OUT operator\n", 2);
		// 		break ;
		// 	}
		// }
		// else if (is_last_node_operator(pars))
		// {
		// 	if (is_last_node_pipe(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_command(pars, u_alloc, &i);
		// 	else if (is_last_node_redir(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_file(pars, cur->cleaned_prompt[i]);
		// 	else if (is_last_node_r_in_delim(pars) && !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
		// 		new_node_here_doc(pars, cur->cleaned_prompt[i]);
		// 	else
		// 	{
		// 		lstfirst(*pars)->MasterKill = true;
		// 		ft_putendl_fd("Two consecutives operators\n", 2);
		// 		break ;
		// 	}
		// }
		if (cur->cleaned_prompt[i])
			i++;
	}
	last_checker(pars);
	// print_final_struct(pars);
}
