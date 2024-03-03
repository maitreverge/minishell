/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pars_linked_list_functions_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:28:41 by flverge           #+#    #+#             */
/*   Updated: 2024/03/03 17:25:58 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_pars	*init_1st_node_pars(void)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return (NULL);
	new->masterkill = false;
	new->error_message = 0;
	new->is_redir_in = false;
	// new->g_last_exit_status = 0;
	new->is_command = false;
	new->cmd = NULL;
	new->is_file = false;
	new->fl = NULL;
	new->is_operator = false;
	new->operator = NULL;
	new->is_here_doc = false;
	new->here_doc = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_pars	*lstfirst(t_pars *lst)
{
	t_pars	*current;

	current = lst;
	if (!current)
		return (0);
	if (!current->prev)
		return (current);
	while (current->prev != NULL)
	{
		current = current->prev;
	}
	return (current);
}
