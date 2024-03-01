/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pars_linked_list_functions_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:28:41 by flverge           #+#    #+#             */
/*   Updated: 2024/03/01 10:58:13 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_pars	*init_1st_node_pars(void)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return (NULL);
	new->MasterKill = false;
	new->error_message = 0;
	new->isRedirIn = false;
	new->last_exit_status = 0;
	new->isCommand = false;
	new->cmd = NULL;
	new->isFile = false;
	new->fl = NULL;
	new->isOperator = false;
	new->operator = NULL;
	new->isHereDoc = false;
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
