/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 04:25:36 by flverge           #+#    #+#             */
/*   Updated: 2024/01/27 04:27:13 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*lstnew(int number, int index)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->nb = number;
	new_node->master_index = index;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_node	*lstlast(t_node *lst)
{
	t_node	*current;

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

void	lstadd_back(t_node **lst, t_node *new)
{
	t_node	*tail;

	tail = lstlast(*lst);
	tail->next = new;
	new->prev = tail;
}

void	lstadd_front(t_node **lst, t_node *new)
{
	t_node	*head;

	head = *lst;
	head->prev = new;
	new->next = head;
	*lst = new;
}

int	lstsize(t_node *lst)
{
	t_node	*current;
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