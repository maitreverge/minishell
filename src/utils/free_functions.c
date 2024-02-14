/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:40:52 by flverge           #+#    #+#             */
/*   Updated: 2024/02/14 09:46:13 by flverge          ###   ########.fr       */
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

void	free_t_pars(t_pars **lst)
{
	t_pars	*temp;

	while ((*lst)->next)
	{
		temp = (*lst)->next;
		free_t_cmd((*lst)->cmd);
		free_t_file((*lst)->fl);
		free((*lst));
		(*lst) = temp;
	}
}

void	free_s_utils(t_utils **utils)
{
	t_utils	*current;

	current = *utils;
	free_split(current->result);
	free(current);
}
