/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/02/16 11:10:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **to_free)
{
	char	**current;
	int		i;
	int 	len;

	if (!to_free)
		return;

	i = 0;
	len = 0;
	current = to_free;
	while (current[len] != NULL)
		len++;
	current = to_free;
	while (i < len)
	{
		if (current[i])
		{
			free(current[i]);
			current[i] = NULL;  // set the pointer to NULL after freeing it
		}
		i++;
	}
	free(to_free);
}

void	free_s_env(t_env_list **env)
{
	t_env_list	*current;
	t_env_list	*temp;

	current = *env;
	while (current)
	{
		temp = current;
		free(current->key);
		free(current->value);
		current = current->next;
		free(temp);
	}
}

void	free_s_utils(t_utils **utils)
{
	t_utils	*current;

	current = *utils;
	free_split(current->result);
	free(current);
}

void	free_firstnode_pars(t_pars **pars)
{
	free(*pars);
}

void	free_t_alloc(t_alloc *alloc)
{
	// t_alloc *to_free;
	
	// to_free = *alloc;
	free_split(alloc->splitted_prompt);
	free_split(alloc->paths);
	// free_split(alloc->cleaned_prompt); // already free in t_utils function
	free(alloc);
}

