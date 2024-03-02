/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pars_linked_list_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 04:25:36 by flverge           #+#    #+#             */
/*   Updated: 2024/03/02 10:33:44 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_pars	*lstnew(int exit_status)
{
	t_pars	*new_node;

	new_node = (t_pars *)malloc(sizeof(t_pars));
	if (!new_node)
		return (NULL);
	new_node->last_exit_status = exit_status;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_pars	*lstlast(t_pars *lst)
{
	t_pars	*current;

	current = lst;
	if (!current)
		return (0);
	if (!current->next)
		return (current);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	lstadd_back(t_pars **lst, t_pars *new)
{
	t_pars	*tail;

	tail = lstlast(*lst);
	tail->next = new;
	new->prev = tail;
}

void	lstadd_front(t_pars **lst, t_pars *new)
{
	t_pars	*head;

	head = *lst;
	head->prev = new;
	new->next = head;
	*lst = new;
}

int	lstsize(t_pars *lst)
{
	t_pars	*current;
	int		i;

	current = lst;
	if (!current)
		return (0);
	else if (!current->next)
		return (1);
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
