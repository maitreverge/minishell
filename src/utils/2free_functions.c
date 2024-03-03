/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2free_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:08:01 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/03 20:44:16 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **to_free)
{
	char	**current;
	int		i;
	int		len;

	if (!to_free)
		return ;
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
		}
		i++;
	}
	free(to_free);
}

// free(*env); // free the node itself was at the end
void	free_s_env(t_env_list **env)
{
	t_env_list	*current;
	t_env_list	*temp;

	current = *env;
	while (current)
	{
		temp = current;
		free(current->original_envp);
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
	if (alloc->splitted_prompt)
		free_split(alloc->splitted_prompt);
	if (alloc->paths)
		free_split(alloc->paths);
	free(alloc);
}
