/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pars_linked_list_functions_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:28:41 by flverge           #+#    #+#             */
/*   Updated: 2024/02/16 15:24:30 by flverge          ###   ########.fr       */
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
