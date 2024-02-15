/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:47:47 by flverge           #+#    #+#             */
/*   Updated: 2024/02/15 11:02:48 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_alloc(t_pars **pars, t_alloc **u_alloc)
{
	t_alloc	*cur;
	t_pars	*last_p_node;
	int		i;

	cur = *u_alloc;
	i = 0;
	search_redir_in(pars, cur->splitted_prompt, cur->cleaned_prompt);
	while (cur->cleaned_prompt[i])
	{
		last_p_node = lstlast(*pars);
		if (!last_p_node->prev)
		{
			if (!is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_command(pars, u_alloc, &i);
			else
			{
				(*pars)->MasterKill = true;
				printf("First Token is a Operator\n");
				break ;
			}
		}
		else if ((is_last_node_cmd(pars)))
		{
			if (is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a command isn't a operator\n");
				break ;
			}
		}
		else if (is_last_node_file(pars))
		{
			if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i])
				|| is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a file isn't a PIPE or RED_OUT operator\n");
				break ;
			}
		}
		else if (is_last_node_here_doc(pars))
		{
			if (is_token_pipe(cur->splitted_prompt[i], cur->cleaned_prompt[i])
				|| is_token_redir_out(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_operator(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("Token following a HERE_DOC isn't a PIPE or RED_OUT operator\n");
				break ;
			}
		}
		else if (is_last_node_operator(pars))
		{
			if (is_last_node_pipe(pars)
				&& !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_command(pars, u_alloc, &i);
			else if (is_last_node_redir(pars)
				&& !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_file(pars, cur->cleaned_prompt[i]);
			else if (is_last_node_r_in_delim(pars)
				&& !is_token_opr(cur->splitted_prompt[i], cur->cleaned_prompt[i]))
				new_node_here_doc(pars, cur->cleaned_prompt[i]);
			else
			{
				(*pars)->MasterKill = true;
				printf("TWO CONSECUTIVE OPERATORS\n\n");
				break ;
			}
		}
		if (cur->cleaned_prompt[i])
			i++;
	}
	// ! Turn this comment off to see on stdout what's in the struct
	print_final_struct(pars);
}
