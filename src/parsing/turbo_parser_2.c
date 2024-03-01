/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 18:00:37 by flverge          ###   ########.fr       */
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

static int	big_norm_1(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	t_pars	*last_p_node;

	last_p_node = lstlast(*pars);
	if (!last_p_node->prev)
	{
		if (alloc_part_1(cur, i, pars, u_alloc))
			return (2);
		else
			return (0);
	}
	else if ((is_last_node_cmd(pars)))
	{
		if (alloc_part_2(cur, i, pars))
			return (2);
		else
			return (0);
	}
	else if (is_last_node_file(pars))
	{
		if (alloc_part_3(cur, i, pars))
			return (2);
		return (0);
	}
	return (1);
}

static bool	big_norm_2(t_alloc *cur, int *i, t_pars **pars, t_alloc **u_alloc)
{
	if (is_last_node_here_doc(pars))
	{
		if (alloc_part_4(cur, i, pars))
			return (true);
	}
	else if (is_last_node_operator(pars))
	{
		if (alloc_part_5(cur, i, pars, u_alloc))
			return (true);
	}
	return (false);
}

void	pars_alloc(t_pars **pars, t_alloc **u_alloc)
{
	t_alloc	*cur;
	int save;
	int		i;

	cur = *u_alloc;
	i = 0;
	search_redir_in(pars, cur->splitted_prompt, cur->cleaned_prompt);
	while (cur->cleaned_prompt[i])
	{
		save = big_norm_1(cur, &i, pars, u_alloc);
		if (save == 2)
			break ;
		else if (save == 1)
		{
			if (big_norm_2(cur, &i, pars, u_alloc))
				break ;
		}
		if (cur->cleaned_prompt[i])
			i++;
	}
	last_checker(pars);
}
