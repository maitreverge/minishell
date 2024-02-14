/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 11:30:12 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **to_free)
{
	char	**current;
	int		i;

	i = 0;
	current = to_free;
	while (current[i])
	{
		free(current[i]);
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
