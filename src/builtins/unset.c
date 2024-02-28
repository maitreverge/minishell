/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:58:42 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 11:59:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	find_middle_node(t_env_list **envp, char *line)
{
	t_env_list *current;
	t_env_list *previous_node;
	t_env_list *next_node;
	t_env_list *temp;
	
	temp = *envp;
	
	while (temp)
	{
		if (!ft_strcmp(temp->key, line))
			break;
		previous_node = temp;
		temp = temp->next;
	}
	if (!temp) // if variable not found, exit function to avoid segfault
		return;
	current = previous_node->next;
	next_node = current->next;
	previous_node->next = next_node;
	free(current);
}

/*Removes 'line' from the list of environment variables*/
void	ft_unset(t_env_list **envp, char *line, t_pars **parsing)
{
	t_env_list *current;
	t_env_list *first_node;
	t_env_list *last_node;
	
	current = *envp;
	first_node = *envp;
	last_node = env_lstlast(*envp);

	// ! CASE 1 : target is on the first node
	if (!ft_strcmp(first_node->key, line))
	{
		(*envp) = (*envp)->next; // move the head of the struct itself to the next node
		free(first_node);
	}
	// ! CASE 2 : target is on the last node
	else if (!ft_strcmp(last_node->key, line))
	{
		while (ft_strcmp(current->next->key, line))
			current = current->next;
		current->next = NULL;
		free(last_node);
	}
	else // ! CASE 3 : the target node is in the middle
		find_middle_node(envp, line);
	lstfirst(*parsing)->last_exit_status = 0; // unset last_exit_status ==> 0 in every case !
}